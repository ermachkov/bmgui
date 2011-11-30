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

template<> Application *Singleton<Application>::mSingleton = NULL;

Application::Application(const std::vector<CL_String> &args, lua_State *luaState)
: mCompanyName("Sibek"), mApplicationName("Balance"), mApplicationVersion("3.0"), mQuit(false)
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
	commandLine.add_option('d', "datadir", "PATH", "Path to the data directory");
	commandLine.parse_args(argv.size(), &argv[0]);

#if defined(WIN32) || defined(__APPLE__)
	mDataDirectory = CL_Directory::get_resourcedata("Game", "data");
#else
	mDataDirectory = CL_PathHelp::add_trailing_slash(GAME_DATA_DIR);
#endif
	while (commandLine.next())
	{
		switch (commandLine.get_key())
		{
		case 'd':
			mDataDirectory = CL_PathHelp::add_trailing_slash(commandLine.get_argument());
			break;
		}
	}

	// load the system profile
	Profile profile("");

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

	// save the system profile
	profile.save();
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
