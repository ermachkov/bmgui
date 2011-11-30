#include "Precompiled.h"
#include "Keyboard.h"
#include "Graphics.h"

template<> Keyboard *Singleton<Keyboard>::mSingleton = NULL;

bool Keyboard::isKeyDown(int key) const
{
	return Graphics::getSingleton().getWindow().get_ic().get_keyboard().get_keycode(key);
}
