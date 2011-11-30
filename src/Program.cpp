#include "Precompiled.h"
#include "Program.h"
#include "Application.h"

CL_ClanApplication Program::mApplication(&Program::main);

int Program::main(const std::vector<CL_String> &args)
{
	CL_UniquePtr<Application> app;
	std::string error;

	try
	{
		app.reset(new Application(args));
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
		console.display_close_message();
		return -1;
	}

	return 0;
}
