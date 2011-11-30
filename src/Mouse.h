#ifndef MOUSE_H
#define MOUSE_H

#include "Singleton.h"

// Mouse class
class Mouse : public Singleton<Mouse>
{
public:

	// Returns the mouse position
	void getPosition(float *x = NULL, float *y = NULL) const;

	// Returns true if the mouse button is pressed
	bool isKeyDown(int key) const;

	// Shows the system cursor
	void showCursor();

	// Hides the system cursor
	void hideCursor();
};

#endif
