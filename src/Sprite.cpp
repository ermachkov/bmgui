#include "Precompiled.h"
#include "Sprite.h"
#include "Application.h"
#include "Graphics.h"
#include "ResourceManager.h"
#include "SpriteResource.h"

Sprite::Sprite(const std::string &name, float x, float y)
: mPos(x, y)
{
	CL_SharedPtr<SpriteResource> resource = cl_dynamic_pointer_cast<SpriteResource>(ResourceManager::getSingleton().getResource(name));
	if (!resource)
		throw Exception(cl_format("Resource '%1' is not a sprite resource", name));
	if (!resource->isLoaded())
		throw Exception(cl_format("Sprite '%1' is not loaded", name));

	// clone the sprite and finish animation
	mSprite.clone(resource->getSprite());
	mSprite.set_rotation_hotspot(origin_top_left);
	mSprite.set_show_on_finish(CL_Sprite::show_first_frame);
	mSprite.finish();

	// multiply the sprite color by alpha since we use premultiplied alpha everywhere
	mColor = mSprite.get_color();
	mSprite.set_color(CL_Colorf(mColor.r * mColor.a, mColor.g * mColor.a, mColor.b * mColor.a, mColor.a));

	// subscribe to the update event
	mSlotUpdate = Application::getSingleton().getSigUpdate().connect(this, &Sprite::onUpdate);
}

float Sprite::get_x() const
{
	return mPos.x;
}

void Sprite::set_x(float x)
{
	mPos.x = x;
}

float Sprite::get_y() const
{
	return mPos.y;
}

void Sprite::set_y(float y)
{
	mPos.y = y;
}

float Sprite::get_red() const
{
	return mColor.r;
}

void Sprite::set_red(float red)
{
	mColor.r = red;
	mSprite.set_color(CL_Colorf(mColor.r * mColor.a, mColor.g * mColor.a, mColor.b * mColor.a, mColor.a));
}

float Sprite::get_green() const
{
	return mColor.g;
}

void Sprite::set_green(float green)
{
	mColor.g = green;
	mSprite.set_color(CL_Colorf(mColor.r * mColor.a, mColor.g * mColor.a, mColor.b * mColor.a, mColor.a));
}

float Sprite::get_blue() const
{
	return mColor.b;
}

void Sprite::set_blue(float blue)
{
	mColor.b = blue;
	mSprite.set_color(CL_Colorf(mColor.r * mColor.a, mColor.g * mColor.a, mColor.b * mColor.a, mColor.a));
}

float Sprite::get_alpha() const
{
	return mColor.a;
}

void Sprite::set_alpha(float alpha)
{
	mColor.a = alpha;
	mSprite.set_color(CL_Colorf(mColor.r * mColor.a, mColor.g * mColor.a, mColor.b * mColor.a, mColor.a));
}

int Sprite::getNumFrames() const
{
	return mSprite.get_frame_count();
}

int Sprite::get_frame() const
{
	return mSprite.get_current_frame();
}

void Sprite::set_frame(int frame)
{
	mSprite.set_frame(frame);
}

int Sprite::getWidth() const
{
	return mSprite.get_width();
}

int Sprite::getHeight() const
{
	return mSprite.get_height();
}

void Sprite::getHotSpot(int *x, int *y) const
{
	CL_Origin origin;
	CL_Point hotspot;
	mSprite.get_alignment(origin, hotspot.x, hotspot.y);

	*x = -hotspot.x;
	*y = -hotspot.y;
}

void Sprite::setHotSpot(int x, int y)
{
	mSprite.set_alignment(origin_top_left, -x, -y);
	mSprite.set_rotation_hotspot(origin_top_left, -x, -y);
}

float Sprite::get_angle() const
{
	return mSprite.get_angle().to_radians();
}

void Sprite::set_angle(float angle)
{
	mSprite.set_angle(CL_Angle(angle, cl_radians));
}

void Sprite::getScale(float *x, float *y) const
{
	mSprite.get_scale(*x, *y);
}

void Sprite::setScale(float x, float y)
{
	mSprite.set_scale(x, y != 0.0f ? y : x);
}

bool Sprite::isPointInside(float x, float y) const
{
	int frame = mSprite.get_current_frame();
	CL_Size size = mSprite.get_frame_size(frame);

	// determine translation in local coordinates
	CL_Origin origin;
	CL_Point hotspot;
	mSprite.get_alignment(origin, hotspot.x, hotspot.y);
	CL_Point trans = hotspot + mSprite.get_frame_offset(frame);

	// retrieve rotation angle
	float angle = mSprite.get_angle().to_radians();

	// retrieve scale factors
	CL_Pointf scale;
	mSprite.get_scale(scale.x, scale.y);

	// convert screen coordinates to sprite local coordinates
	float xloc, yloc;
	if (angle == 0.0f)
	{
		xloc = (x - mPos.x) / scale.x - trans.x;
		yloc = (y - mPos.y) / scale.y - trans.y;
	}
	else
	{
		float sina = sin(angle), cosa = cos(angle);
		float A = x - mPos.x - scale.x * trans.x * cosa + scale.y * trans.y * sina;
		float B = y - mPos.y - scale.x * trans.x * sina - scale.y * trans.y * cosa;
		xloc = (A * cosa + B * sina) / scale.x;
		yloc = (-A * sina + B * cosa) / scale.y;
	}

	return xloc >= 0.0f && xloc < size.width && yloc >= 0.0f && yloc < size.height;
}

void Sprite::draw()
{
	mSprite.draw(Graphics::getSingleton().getWindow().get_gc(), mPos.x, mPos.y);
}

void Sprite::draw(float x, float y)
{
	mSprite.draw(Graphics::getSingleton().getWindow().get_gc(), x, y);
}

void Sprite::draw(float x1, float y1, float x2, float y2)
{
	mSprite.draw(Graphics::getSingleton().getWindow().get_gc(), CL_Rectf(x1, y1, x2, y2));
}

void Sprite::draw(float x1, float y1, float x2, float y2, float sx1, float sy1, float sx2, float sy2)
{
	mSprite.draw(Graphics::getSingleton().getWindow().get_gc(), CL_Rectf(sx1, sy1, sx2, sy2), CL_Rectf(x1, y1, x2, y2));
}

void Sprite::onUpdate(int delta)
{
	mSprite.update(delta);
}
