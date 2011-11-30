#include "Precompiled.h"
#include "LuaScript.h"
#include "Application.h"
#include "Graphics.h"

TOLUA_API int tolua_LuaBindings_open(lua_State *luaState);

LuaScript::LuaScript(const std::string &fileName, lua_State *luaState)
: mLuaState(luaState), mOwnLuaState(mLuaState == NULL), mWidth(0), mHeight(0)
{
	// create new Lua state if needed
	if (mOwnLuaState)
	{
		mLuaState = luaL_newstate();
		if (mLuaState == NULL)
			throw Exception("Failed to create new Lua state");
		luaL_openlibs(mLuaState);
	}

	// export engine functions to Lua
	tolua_LuaBindings_open(mLuaState);

	// load and execute main Lua script
	if (mOwnLuaState)
	{
		CL_File file(Application::getSingleton().getDataDirectory() + fileName);
		int size = file.get_size();
		if (size == 0)
			throw Exception("Script file '" + fileName + "' is empty");

		CL_DataBuffer buf(size);
		if (file.read(buf.get_data(), size) != size)
			throw Exception("Failed to read the script file '" + fileName + "'");

		int stackSize = lua_gettop(mLuaState);

		lua_pushcfunction(mLuaState, errorHandler);
		if (luaL_loadbuffer(mLuaState, buf.get_data(), size, fileName.c_str()) != 0)
			throw Exception("Failed to compile Lua script: " + std::string(lua_tostring(mLuaState, -1)));
		if (lua_pcall(mLuaState, 0, 0, -2) != 0)
			throw Exception("Failed to execute Lua script: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);

		GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
	}

	// subscribe to the various game signals
	mSlots.connect(Application::getSingleton().getSigInit(), this, &LuaScript::onInit);
	mSlots.connect(Application::getSingleton().getSigUpdate(), this, &LuaScript::onUpdate);
	mSlots.connect(Application::getSingleton().getSigQuit(), this, &LuaScript::onQuit);

	CL_DisplayWindow &window = Graphics::getSingleton().getWindow();
	mSlots.connect(window.sig_window_minimized(), this, &LuaScript::onMinimize);
	mSlots.connect(window.sig_window_restored(), this, &LuaScript::onRestore);
	mSlots.connect(window.sig_resize(), this, &LuaScript::onResize);

	CL_InputDevice &keyboard = window.get_ic().get_keyboard();
	mSlots.connect(keyboard.sig_key_down(), this, &LuaScript::onKeyDown);
	mSlots.connect(keyboard.sig_key_up(), this, &LuaScript::onKeyUp);

	CL_InputDevice &mouse = window.get_ic().get_mouse();
	mSlots.connect(mouse.sig_key_down(), this, &LuaScript::onMouseDown);
	mSlots.connect(mouse.sig_key_dblclk(), this, &LuaScript::onMouseDown);
	mSlots.connect(mouse.sig_key_up(), this, &LuaScript::onMouseUp);
}

LuaScript::~LuaScript()
{
	if (mOwnLuaState && mLuaState != NULL)
		lua_close(mLuaState);
}

void LuaScript::onInit()
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onInit");
	if (lua_isfunction(mLuaState, -1))
	{
		if (lua_pcall(mLuaState, 0, 0, -2) != 0)
			throw Exception("Failed to execute 'onInit' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onUpdate(int delta)
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onUpdate");
	if (lua_isfunction(mLuaState, -1))
	{
		lua_pushnumber(mLuaState, delta);
		if (lua_pcall(mLuaState, 1, 0, -3) != 0)
			throw Exception("Failed to execute 'onUpdate' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onQuit()
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onQuit");
	if (lua_isfunction(mLuaState, -1))
	{
		if (lua_pcall(mLuaState, 0, 0, -2) != 0)
			throw Exception("Failed to execute 'onQuit' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onMinimize()
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onMinimize");
	if (lua_isfunction(mLuaState, -1))
	{
		if (lua_pcall(mLuaState, 0, 0, -2) != 0)
			throw Exception("Failed to execute 'onMinimize' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onRestore()
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onRestore");
	if (lua_isfunction(mLuaState, -1))
	{
		if (lua_pcall(mLuaState, 0, 0, -2) != 0)
			throw Exception("Failed to execute 'onRestore' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onResize(int width, int height)
{
	if (width == 0 || height == 0 || (width == mWidth && height == mHeight))
		return;

	mWidth = width;
	mHeight = height;

	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onResize");
	if (lua_isfunction(mLuaState, -1))
	{
		float x1, y1, x2, y2;
		Graphics::getSingleton().getVisibleRect(&x1, &y1, &x2, &y2);
		lua_pushnumber(mLuaState, x1);
		lua_pushnumber(mLuaState, y1);
		lua_pushnumber(mLuaState, x2);
		lua_pushnumber(mLuaState, y2);
		if (lua_pcall(mLuaState, 4, 0, -6) != 0)
			throw Exception("Failed to execute 'onResize' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onKeyDown");
	if (lua_isfunction(mLuaState, -1))
	{
		lua_pushnumber(mLuaState, key.id);
		lua_pushstring(mLuaState, key.str.c_str());
		if (lua_pcall(mLuaState, 2, 0, -4) != 0)
			throw Exception("Failed to execute 'onKeyDown' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onKeyUp(const CL_InputEvent &key, const CL_InputState &state)
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onKeyUp");
	if (lua_isfunction(mLuaState, -1))
	{
		lua_pushnumber(mLuaState, key.id);
		if (lua_pcall(mLuaState, 1, 0, -3) != 0)
			throw Exception("Failed to execute 'onKeyUp' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onMouseDown(const CL_InputEvent &key, const CL_InputState &state)
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onMouseDown");
	if (lua_isfunction(mLuaState, -1))
	{
		CL_Pointf pt = Graphics::getSingleton().screenToVirtual(key.mouse_pos);
		lua_pushnumber(mLuaState, pt.x);
		lua_pushnumber(mLuaState, pt.y);
		lua_pushnumber(mLuaState, key.id);
		if (lua_pcall(mLuaState, 3, 0, -5) != 0)
			throw Exception("Failed to execute 'onMouseDown' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

void LuaScript::onMouseUp(const CL_InputEvent &key, const CL_InputState &state)
{
	int stackSize = lua_gettop(mLuaState);

	lua_pushcfunction(mLuaState, errorHandler);
	lua_getglobal(mLuaState, "onMouseUp");
	if (lua_isfunction(mLuaState, -1))
	{
		CL_Pointf pt = Graphics::getSingleton().screenToVirtual(key.mouse_pos);
		lua_pushnumber(mLuaState, pt.x);
		lua_pushnumber(mLuaState, pt.y);
		lua_pushnumber(mLuaState, key.id);
		if (lua_pcall(mLuaState, 3, 0, -5) != 0)
			throw Exception("Failed to execute 'onMouseUp' event handler: " + std::string(lua_tostring(mLuaState, -1)));
		lua_pop(mLuaState, 1);
	}
	else
	{
		lua_pop(mLuaState, 2);
	}

	GAME_ASSERT(lua_gettop(mLuaState) == stackSize);
}

int LuaScript::errorHandler(lua_State *luaState)
{
	// check the error message on the top
	if (!lua_isstring(luaState, -1))
		return 1;

	// retrieve and call 'debug.traceback' function
	lua_getglobal(luaState, "debug");
	if (!lua_istable(luaState, -1))
	{
		lua_pop(luaState, 1);
		return 1;
	}

	lua_getfield(luaState, -1, "traceback");
	if (!lua_isfunction(luaState, -1))
	{
		lua_pop(luaState, 2);
		return 1;
	}
	lua_remove(luaState, -2);

	lua_pushvalue(luaState, -2);
	lua_remove(luaState, -3);
	lua_pushinteger(luaState, 2);
	lua_call(luaState, 2, 1);

	// return the complete error message on the stack
	return 1;
}
