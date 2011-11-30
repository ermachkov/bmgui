#ifndef SPRITE_H
#define SPRITE_H

// Sprite class
class Sprite
{
public:

	// Constructor
	Sprite(const std::string &name, float x, float y);

	// Returns x coordinate
	float get_x() const;

	// Sets x coordinate
	void set_x(float x);

	// Returns y coordinate
	float get_y() const;

	// Sets y coordinate
	void set_y(float y);

	// Returns red color component
	float get_red() const;

	// Sets red color component
	void set_red(float red);

	// Returns green color component
	float get_green() const;

	// Sets green color component
	void set_green(float green);

	// Returns blue color component
	float get_blue() const;

	// Sets blue color component
	void set_blue(float blue);

	// Returns alpha color component
	float get_alpha() const;

	// Sets alpha color component
	void set_alpha(float alpha);

	// Returns the total number of animation frames
	int getNumFrames() const;

	// Returns the current animation frame
	int get_frame() const;

	// Sets the current animation frame
	void set_frame(int frame);

	// Returns the sprite width
	int getWidth() const;

	// Returns the sprite height
	int getHeight() const;

	// Returns the sprite hotspot
	void getHotSpot(int *x = NULL, int *y = NULL) const;

	// Sets the sprite hotspot
	void setHotSpot(int x, int y);

	// Returns the sprite rotation angle
	float get_angle() const;

	// Sets the sprite rotation angle
	void set_angle(float angle);

	// Returns the scale factors
	void getScale(float *x = NULL, float *y = NULL) const;

	// Sets the scale factors
	void setScale(float x, float y = 0.0f);

	// Tests if a point is inside the sprite
	bool isPointInside(float x, float y) const;

	// Draws the sprite
	void draw();

	// Draws the sprite in specified point
	void draw(float x, float y);

	// Draws the sprite in specified rectangle
	void draw(float x1, float y1, float x2, float y2);

	// Draws the part of sprite in specified rectangle
	void draw(float x1, float y1, float x2, float y2, float sx1, float sy1, float sx2, float sy2);

private:

	// Update event handler
	void onUpdate(int delta);

	CL_Sprite   mSprite;        // Sprite object
	CL_Slot     mSlotUpdate;    // Update event slot
	CL_Pointf   mPos;           // Sprite position
	CL_Colorf   mColor;         // Sprite color
};

#endif
