#include "Precompiled.h"
#include "Graphics.h"
#include "Application.h"
#include "FontResource.h"
#include "Profile.h"
#include "ResourceManager.h"

template<> Graphics *Singleton<Graphics>::mSingleton = NULL;

Graphics::Graphics(Profile &profile)
: mMinAspect(0.0f), mMaxAspect(0.0f), mVSync(true), mFPSTime(0), mNumFrames(0), mFPS(0.0f), mBlendMode(BLEND_ALPHA)
{
	// setup the graphics settings
	CL_DisplayWindowDescription desc;
	desc.set_title("Balance");
	desc.set_size(CL_Size(profile.getInt("width", 1024), profile.getInt("height", 768)), true);
	desc.set_swap_interval(mVSync ? 1 : 0);
	if (profile.getBool("fullscreen", true))
	{
		desc.set_decorations(false);
		desc.set_fullscreen(true);
	}
	else
	{
		desc.set_allow_resize(true);
	}
	mWindow = CL_DisplayWindow(desc);

	// make window visible while debugging under SciTE
	mWindow.show();

	// connect window signals
	mSlots.connect(Application::getSingleton().getSigUpdate(), this, &Graphics::onUpdate);
	mSlots.connect(mWindow.get_ic().get_mouse().sig_key_down(), this, &Graphics::onMouseDown);
	mSlots.connect(mWindow.get_ic().get_mouse().sig_key_dblclk(), this, &Graphics::onMouseDown);
	mSlots.connect(mWindow.get_ic().get_mouse().sig_key_up(), this, &Graphics::onMouseUp);
	mSlots.connect(mWindow.sig_resize(), this, &Graphics::onResize);
	mSlots.connect(mWindow.sig_window_close(), this, &Graphics::onClose);

	// initialize the graphics settings
	mWindow.get_gc().set_map_mode(cl_user_projection);
	setScreenSize(1024.0f, 768.0f);
	setBlendMode(mBlendMode);

	// save the current settings
	profile.setBool("fullscreen", desc.is_fullscreen());
	profile.setInt("width", desc.get_size().width);
	profile.setInt("height", desc.get_size().height);
}

CL_DisplayWindow &Graphics::getWindow()
{
	return mWindow;
}

CL_Point Graphics::virtualToScreen(const CL_Pointf &pt) const
{
	return CL_Point(static_cast<int>(pt.x / mScreenSize.width * mViewport.get_width() + mViewport.left + 0.5f),
		static_cast<int>(pt.y / mScreenSize.height * mViewport.get_height() + mViewport.top + 0.5f));
}

CL_Pointf Graphics::screenToVirtual(const CL_Point &pt) const
{
	return CL_Pointf((pt.x - mViewport.left) / mViewport.get_width() * mScreenSize.width,
		(pt.y - mViewport.top) / mViewport.get_height() * mScreenSize.height);
}

void Graphics::setScreenSize(float width, float height, float minAspect, float maxAspect)
{
	mScreenSize.width = width;
	mScreenSize.height = height;

	if (minAspect != 0.0f && maxAspect != 0.0f)
	{
		mMinAspect = minAspect;
		mMaxAspect = maxAspect;
	}
	else
	{
		mMinAspect = mMaxAspect = width / height;
	}

	onResize(mWindow.get_viewport().get_width(), mWindow.get_viewport().get_height());
}

void Graphics::getVisibleRect(float *x1, float *y1, float *x2, float *y2) const
{
	*x1 = mVisibleRect.left;
	*y1 = mVisibleRect.top;
	*x2 = mVisibleRect.right;
	*y2 = mVisibleRect.bottom;
}

void Graphics::show()
{
	mWindow.show();
	mWindow.bring_to_front();
}

void Graphics::hide()
{
	mWindow.hide();
}

bool Graphics::isVSync() const
{
	return mVSync;
}

void Graphics::setVSync(bool vsync)
{
	mVSync = vsync;
}

float Graphics::getFPS() const
{
	return mFPS;
}

BlendMode Graphics::getBlendMode() const
{
	return mBlendMode;
}

void Graphics::setBlendMode(BlendMode blendMode)
{
	CL_BlendMode mode;

	switch (blendMode)
	{
	case BLEND_DISABLE:
		mode.enable_blending(false);
		break;

	case BLEND_ALPHA:
		mode.set_blend_function(cl_blend_one, cl_blend_one_minus_src_alpha, cl_blend_one, cl_blend_one_minus_src_alpha);
		break;

	case BLEND_ADD:
		mode.set_blend_function(cl_blend_one, cl_blend_one, cl_blend_one, cl_blend_one);
		break;

	case BLEND_SUBTRACT:
		mode.set_blend_equation(cl_blend_equation_reverse_subtract, cl_blend_equation_reverse_subtract);
		mode.set_blend_function(cl_blend_one, cl_blend_one, cl_blend_one, cl_blend_one);
		break;

	case BLEND_MULTIPLY:
		mode.set_blend_function(cl_blend_dest_color, cl_blend_one_minus_src_alpha, cl_blend_dest_color, cl_blend_one_minus_src_alpha);
		break;
	}

	mBlendMode = blendMode;
	mWindow.get_gc().set_blend_mode(mode);
}

void Graphics::setClipRect(float x1, float y1, float x2, float y2)
{
	// (0, 0) is the lower left corner, since we use our custom projection matrix, not ClanLib standard one
	CL_Point topLeft = virtualToScreen(CL_Pointf(x1, y1));
	CL_Point bottomRight = virtualToScreen(CL_Pointf(x2, y2));
	int height = mWindow.get_viewport().get_height();
	mWindow.get_gc().set_cliprect(CL_Rect(topLeft.x, height - bottomRight.y, bottomRight.x, height - topLeft.y));
}

void Graphics::resetClipRect()
{
	mWindow.get_gc().reset_cliprect();
}

void Graphics::clear(float r, float g, float b)
{
	mWindow.get_gc().clear(CL_Colorf(r, g, b));
}

void Graphics::fillRect(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	CL_Draw::fill(mWindow.get_gc(), x1, y1, x2, y2, CL_Colorf(r * a, g * a, b * a, a));
}

void Graphics::gradientFill(float x1, float y1, float x2, float y2, float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2)
{
	CL_Draw::gradient_fill(mWindow.get_gc(), x1, y1, x2, y2, CL_Gradient(CL_Colorf(r1, g1, b1, a1), CL_Colorf(r2, g2, b2, a2)));
}

void Graphics::flip()
{
	mWindow.flip(mVSync ? 1 : 0);
	++mNumFrames;
}

void Graphics::onUpdate(int delta)
{
	mFPSTime += delta;
	if (mFPSTime >= FPS_PERIOD)
	{
		mFPS = mNumFrames * 1000.0f / mFPSTime;
		mFPSTime -= FPS_PERIOD;
		mNumFrames = 0;
	}
}

void Graphics::onMouseDown(const CL_InputEvent &key, const CL_InputState &state)
{
	mWindow.capture_mouse(true);
}

void Graphics::onMouseUp(const CL_InputEvent &key, const CL_InputState &state)
{
	mWindow.capture_mouse(false);
}

void Graphics::onResize(int width, int height)
{
	if (width == 0 || height == 0)
		return;

	float w = static_cast<float>(width);
	float h = static_cast<float>(height);

	// calculate integer viewport coordinates
	float aspect = w / h;
	if (aspect < mMinAspect)
	{
		// add borders to the top and bottom
		float hn = w / mMinAspect;
		mViewport = CL_Rectf(0.0f, floor((h - hn) / 2.0f + 0.5f), w, floor((h + hn) / 2.0f + 0.5f));
	}
	else if (aspect > mMaxAspect)
	{
		// add borders to the left and right
		float wn = h * mMaxAspect;
		mViewport = CL_Rectf(floor((w - wn) / 2.0f + 0.5f), 0.0f, floor((w + wn) / 2.0f + 0.5f), h);
	}
	else
	{
		// don't add any borders
		mViewport = CL_Rectf(0.0f, 0.0f, w, h);
	}

	// determine the visible rectangle from the viewport aspect ratio
	float wn = mScreenSize.height * (mViewport.get_width() / mViewport.get_height());
	mVisibleRect = CL_Rectf((mScreenSize.width - wn) / 2.0f, 0.0f, (mScreenSize.width + wn) / 2.0f, mScreenSize.height);

	mWindow.get_gc().set_viewport(mViewport);
	mWindow.get_gc().set_projection(CL_Mat4f::ortho_2d(mVisibleRect.left, mVisibleRect.right, mVisibleRect.bottom, mVisibleRect.top));
}

void Graphics::onClose()
{
	Application::getSingleton().quit();
}
