#include "Precompiled.h"
#include "Mouse.h"
#include "Graphics.h"

template<> Mouse *Singleton<Mouse>::mSingleton = NULL;

void Mouse::getPosition(float *x, float *y) const
{
	CL_Point screenPos = Graphics::getSingleton().getWindow().get_ic().get_mouse().get_position();
	CL_Pointf virtualPos = Graphics::getSingleton().screenToVirtual(screenPos);
	*x = virtualPos.x;
	*y = virtualPos.y;
}

bool Mouse::isKeyDown(int key) const
{
	return Graphics::getSingleton().getWindow().get_ic().get_mouse().get_keycode(key);
}

void Mouse::showCursor()
{
	Graphics::getSingleton().getWindow().show_cursor();
}

void Mouse::hideCursor()
{
	Graphics::getSingleton().getWindow().hide_cursor();
}
