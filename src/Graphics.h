#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Singleton.h"

// Blending modes
enum BlendMode
{
	BLEND_DISABLE,      // Blending is disabled
	BLEND_ALPHA,        // Premultiplied alpha blending mode
	BLEND_ADD,          // Additive blending mode
	BLEND_SUBTRACT,     // Subtractive blending mode
	BLEND_MULTIPLY      // Multiplicative blending mode
};

class Profile;

// Graphics engine
class Graphics : public Singleton<Graphics>
{
public:

	// Constructor
	Graphics(Profile &profile);

	// Returns the display window
	CL_DisplayWindow &getWindow();

	// Converts virtual coordinates to screen coordinates
	CL_Point virtualToScreen(const CL_Pointf &pt) const;

	// Converts screen coordinates to virtual coordinates
	CL_Pointf screenToVirtual(const CL_Point &pt) const;

	// Sets the virtual screen size
	void setScreenSize(float width, float height, float minAspect = 0.0f, float maxAspect = 0.0f);

	// Returns the visible rectangle on the virtual screen
	void getVisibleRect(float *x1 = NULL, float *y1 = NULL, float *x2 = NULL, float *y2 = NULL) const;

	// Returns the current vertical synchronization flag
	bool isVSync() const;

	// Sets the vertical synchronization flag
	void setVSync(bool vsync);

	// Returns the current FPS
	float getFPS() const;

	// Returns the blending mode
	BlendMode getBlendMode() const;

	// Sets the blending mode
	void setBlendMode(BlendMode blendMode);

	// Sets the clip rectangle
	void setClipRect(float x1, float y1, float x2, float y2);

	// Resets the clip rectangle
	void resetClipRect();

	// Clears the screen
	void clear(float r, float g, float b);

	// Fills a rectangle with specified color
	void fillRect(float x1, float y1, float x2, float y2, float r, float g, float b, float a);

	// Fills a rectangle with gradient
	void gradientFill(float x1, float y1, float x2, float y2, float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2);

	// Flips back and front buffers
	void flip();

private:

	// FPS measurements period
	static const int FPS_PERIOD = 1000;

	// Update event handler
	void onUpdate(int delta);

	// Mouse down event handler
	void onMouseDown(const CL_InputEvent &key, const CL_InputState &state);

	// Mouse up event handler
	void onMouseUp(const CL_InputEvent &key, const CL_InputState &state);

	// Resize event handler
	void onResize(int width, int height);

	// Close event handler
	void onClose();

	CL_DisplayWindow    mWindow;        // Display window
	CL_SlotContainer    mSlots;         // Slot container
	CL_Sizef            mScreenSize;    // Virtual screen size
	float               mMinAspect;     // Minimum screen aspect ratio
	float               mMaxAspect;     // Maximum screen aspect ratio
	CL_Rectf            mViewport;      // Current viewport in screen coordinates
	CL_Rectf            mVisibleRect;   // Current visible rectangle in virtual coordinates
	bool                mVSync;         // Vertical synchronization flag
	int                 mFPSTime;       // FPS time counter
	int                 mNumFrames;     // Number of frames rendered so far
	float               mFPS;           // Current FPS value
	BlendMode           mBlendMode;     // Current blending mode
};

#endif
