#include "Precompiled.h"
#include "Application.h"
#include "Balance.h"
#include "Database.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "LuaScript.h"
#include "Mouse.h"
#include "Profile.h"
#include "ResourceManager.h"
#include "ResourceQueue.h"
#ifndef WIN32
#include <unistd.h>
#endif

template<> Application *Singleton<Application>::mSingleton = NULL;

Application::Application(const std::vector<CL_String> &args, lua_State *luaState)
: mUpdated(false), mCompanyName(""), mApplicationName("bmgui"), mApplicationVersion(""), mQuit(false)
{
	GAME_ASSERT(!args.empty());

#ifdef WIN32
	// bind main thread to the first core for correct timings on some multicore systems
	SetThreadAffinityMask(GetCurrentThread(), 0x01);
#endif

	// parse the command line arguments
	std::vector<char *> argv;
	for (std::vector<CL_String>::const_iterator it = args.begin(); it != args.end(); ++it)
		argv.push_back(const_cast<char *>(it->c_str()));

	CL_CommandLine commandLine;
	commandLine.set_help_indent(40);
	commandLine.add_doc("Graphical interface for Sibek balance machines");
	commandLine.add_usage("[OPTION...]\n");

	commandLine.add_option('g', "gateway", "ADDR", "Default gateway address");
	commandLine.add_option('a', "local_addr", "ADDR", "Local address");
	commandLine.add_option('m', "netmask", "ADDR", "Subnet mask");
	commandLine.add_option('d', "dns", "ADDR", "DNS server address");
	commandLine.add_option('i', "input_dev", "TYPE", "Input device type");
	commandLine.add_option('s', "server_status", "FLAG", "Server status");
	commandLine.add_option('u', "available_update_version", "VERSION", "Available update version");
	commandLine.add_option('U', "updated", "FLAG", "Software update flag");
	commandLine.add_option('D', "datadir", "PATH", "Path to the data directory");
	commandLine.add_option('h', "help", "", "Show this help");
	commandLine.parse_args(argv.size(), &argv[0]);

#if defined(WIN32) || defined(__APPLE__)
	mDataDirectory = CL_Directory::get_resourcedata("bmgui", "data");
#else
	mDataDirectory = CL_PathHelp::add_trailing_slash(GAME_DATA_DIR);
#endif
	while (commandLine.next())
	{
		switch (commandLine.get_key())
		{
		case 'g':
			mGateway = commandLine.get_argument();
			break;
		case 'a':
			mLocalAddr = commandLine.get_argument();
			break;
		case 'm':
			mNetmask = commandLine.get_argument();
			break;
		case 'd':
			mDNS = commandLine.get_argument();
			break;
		case 'i':
			mInputDev = commandLine.get_argument();
			break;
		case 's':
			mServerStatus = commandLine.get_argument();
			break;
		case 'u':
			mAvailableUpdateVersion = commandLine.get_argument();
			break;
		case 'U':
			mUpdated = CL_StringHelp::text_to_bool(commandLine.get_argument());
			break;
		case 'D':
			mDataDirectory = CL_PathHelp::add_trailing_slash(commandLine.get_argument());
			break;
		case 'h':
			commandLine.print_help();
			quit();
			return;
		}
	}

	/*CL_Console::write_line(cl_format("mGateway = %1", mGateway));
	CL_Console::write_line(cl_format("mLocalAddr = %1", mLocalAddr));
	CL_Console::write_line(cl_format("mNetmask = %1", mNetmask));
	CL_Console::write_line(cl_format("mDNS = %1", mDNS));
	CL_Console::write_line(cl_format("mInputDev = %1", mInputDev));
	CL_Console::write_line(cl_format("mServerStatus = %1", mServerStatus));
	CL_Console::write_line(cl_format("mAvailableUpdateVersion = %1", mAvailableUpdateVersion));
	CL_Console::write_line(cl_format("mDataDirectory = %1", mDataDirectory));*/

	// load the system profile
	Profile profile("");

	CL_Console::write_line(cl_format("gateway = %1", profile.getString("gateway")));
	CL_Console::write_line(cl_format("local_addr = %1", profile.getString("local_addr")));
	CL_Console::write_line(cl_format("netmask = %1", profile.getString("netmask")));
	CL_Console::write_line(cl_format("dns = %1", profile.getString("dns")));
	CL_Console::write_line(cl_format("input_dev = %1", profile.getInt("input_dev")));
	CL_Console::write_line(cl_format("server_status = %1", profile.getBool("server_status")));
	CL_Console::write_line(cl_format("available_update_version = %1", profile.getString("available_update_version")));
	CL_Console::write_line(cl_format("server_addr = %1", profile.getString("server_addr")));
	CL_Console::write_line(cl_format("remote_control = %1", profile.getBool("remote_control")));
	CL_Console::write_line(cl_format("ignored_update_version = %1", profile.getString("ignored_update_version")));
	CL_Console::write_line(cl_format("cal_command = %1", profile.getString("cal_command")));
	CL_Console::write_line(cl_format("language = %1", profile.getInt("language")));
	CL_Console::write_line(cl_format("fullscreen = %1", profile.getBool("fullscreen")));
	CL_Console::write_line(cl_format("width = %1", profile.getInt("width")));
	CL_Console::write_line(cl_format("height = %1", profile.getInt("height")));

	// initialize all game subsystems
	mBalance = CL_SharedPtr<Balance>(new Balance(profile));
	mDatabase = CL_SharedPtr<Database>(new Database(getConfigDirectory() + getApplicationName() + ".db"));
	mResourceManager = CL_SharedPtr<ResourceManager>(new ResourceManager());
	mResourceQueue = CL_SharedPtr<ResourceQueue>(new ResourceQueue());
	mGraphics = CL_SharedPtr<Graphics>(new Graphics(profile));
	mKeyboard = CL_SharedPtr<Keyboard>(new Keyboard());
	mMouse = CL_SharedPtr<Mouse>(new Mouse());
	mSoundOutput = CL_SoundOutput(44100);
	mLuaScript = CL_SharedPtr<LuaScript>(new LuaScript("main.lua", luaState));
}

CL_Signal_v0 &Application::getSigInit()
{
	return mSigInit;
}

CL_Signal_v1<int> &Application::getSigUpdate()
{
	return mSigUpdate;
}

CL_Signal_v0 &Application::getSigQuit()
{
	return mSigQuit;
}

std::string Application::getConfigDirectory() const
{
	return CL_Directory::get_appdata(mCompanyName, mApplicationName, mApplicationVersion);
}

std::string Application::getDataDirectory() const
{
	return mDataDirectory;
}

bool Application::isUpdated() const
{
	return mUpdated;
}

std::string Application::getCompanyName() const
{
	return mCompanyName;
}

void Application::setCompanyName(const std::string &name)
{
	mCompanyName = name;
}

std::string Application::getApplicationName() const
{
	return mApplicationName;
}

void Application::setApplicationName(const std::string &name)
{
	mApplicationName = name;
}

std::string Application::getApplicationVersion() const
{
	return mApplicationVersion;
}

void Application::setApplicationVersion(const std::string &version)
{
	mApplicationVersion = version;
}

void Application::run()
{
	mSigInit.invoke();

	unsigned lastTime = CL_System::get_time();
	while (!mQuit)
	{
		unsigned currTime = CL_System::get_time();
		int delta = cl_clamp(static_cast<int>(currTime - lastTime), 0, 1000);
		lastTime = currTime;

		CL_KeepAlive::process();

		if (delta != 0)
			mSigUpdate.invoke(delta);

		mGraphics->flip();
	}

	mSigQuit.invoke();
}

void Application::quit()
{
	mQuit = true;
}
