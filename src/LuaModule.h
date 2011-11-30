#ifndef LUA_MODULE_H
#define LUA_MODULE_H

// Lua module class
class LuaModule
{
public:

	// Lua module main function
	static int main(const std::vector<CL_String> &args, lua_State *luaState);
};

#endif
