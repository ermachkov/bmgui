#include "Precompiled.h"
#include "LuaModule.h"
#include "Application.h"

int LuaModule::main(const std::vector<CL_String> &args, lua_State *luaState)
{
	CL_UniquePtr<Application> app;
	std::string error;

	try
	{
		app.reset(new Application(args, luaState));
		app->run();
	}
	catch (const Exception &exception)
	{
		error = "ERROR: " + exception.get_message_and_stack_trace();
	}
	catch (const CL_Exception &exception)
	{
		error = "CLANLIB ERROR: " + exception.get_message_and_stack_trace();
	}
	catch (const std::exception &exception)
	{
		error = "STD ERROR: " + std::string(exception.what());
	}
	catch (...)
	{
		error = "UNKNOWN ERROR: Unknown exception has been caught";
	}

	if (!error.empty())
	{
		app.reset();
		CL_ConsoleWindow console("Error", 80, 100);
		CL_Console::write_line(error);
#ifdef WIN32
		// make window visible while debugging under SciTE
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
		console.display_close_message();
		exit(-1);
	}

	// return only one value - the module name in the stack
	return 1;
}

#if defined(WIN32) && defined(_DLL)
extern "C" __declspec(dllexport) int luaopen_Balance(lua_State *luaState)
#else
extern "C" int luaopen_Balance(lua_State *luaState)
#endif
{
	std::string cmd;
	lua_getglobal(luaState, "GAME_COMMAND_LINE");
	if (lua_isstring(luaState, -1))
		cmd = lua_tostring(luaState, -1);
	lua_pop(luaState, 1);

	// initialize the array with single required argument
	std::vector<CL_String> args;
	args.push_back("Game");

	// extract all arguments from the command line, properly handling double quotes
	std::string::size_type start, end;
	for (start = cmd.find_first_not_of(" \t"); start != std::string::npos; start = cmd.find_first_not_of(" \t", end))
	{
		std::string arg;
		for (end = cmd.find_first_of(" \t\"", start); end != std::string::npos && cmd[end] == '"'; end = cmd.find_first_of(" \t\"", start))
		{
			arg += cmd.substr(start, end - start);
			start = end + 1;
			end = cmd.find('"', start);
			if (end == std::string::npos)
				break;
			arg += cmd.substr(start, end - start);
			start = end + 1;
		}
		arg += cmd.substr(start, end - start);
		args.push_back(arg);
	}

	return LuaModule::main(args, luaState);
}
