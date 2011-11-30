#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Singleton.h"

// Keyboard class
class Keyboard : public Singleton<Keyboard>
{
public:

	// Returns true if the key is pressed
	bool isKeyDown(int key) const;
};

#endif
