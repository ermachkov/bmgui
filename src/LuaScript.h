#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

// Lua script class
class LuaScript
{
public:

	// Constructor
	LuaScript(const std::string &fileName, lua_State *luaState = NULL);

	// Destructor
	~LuaScript();

private:

	// Init event handler
	void onInit();

	// Update event handler
	void onUpdate(int delta);

	// Quit event handler
	void onQuit();

	// Minimize event handler
	void onMinimize();

	// Restore event handler
	void onRestore();

	// Resize event handler
	void onResize(int width, int height);

	// Key down event handler
	void onKeyDown(const CL_InputEvent &key, const CL_InputState &state);

	// Key up event handler
	void onKeyUp(const CL_InputEvent &key, const CL_InputState &state);

	// Mouse down event handler
	void onMouseDown(const CL_InputEvent &key, const CL_InputState &state);

	// Mouse up event handler
	void onMouseUp(const CL_InputEvent &key, const CL_InputState &state);

	// Lua error handler
	static int errorHandler(lua_State *luaState);

	lua_State           *mLuaState;     // Lua state structure
	bool                mOwnLuaState;   // Is the state is own or not
	CL_SlotContainer    mSlots;         // Slot container for game signals
	int                 mWidth;         // Current window width
	int                 mHeight;        // Current window height
};

#endif
