#ifndef APPLICATION_H
#define APPLICATION_H

#include "Singleton.h"

class Balance;
class Database;
class Graphics;
class Keyboard;
class LuaScript;
class Mouse;
class ResourceManager;
class ResourceQueue;

// Game application class
class Application : public Singleton<Application>
{
public:

	// Constructor
	Application(const std::vector<CL_String> &args, lua_State *luaState = NULL);

	// Returns the init signal
	CL_Signal_v0 &getSigInit();

	// Returns the update signal
	CL_Signal_v1<int> &getSigUpdate();

	// Returns the quit signal
	CL_Signal_v0 &getSigQuit();

	// Returns path to the configuration directory
	std::string getConfigDirectory() const;

	// Returns path to the data directory
	std::string getDataDirectory() const;

	// Returns the company name
	std::string getCompanyName() const;

	// Sets the company name
	void setCompanyName(const std::string &name);

	// Returns the application name
	std::string getApplicationName() const;

	// Sets the application name
	void setApplicationName(const std::string &name);

	// Returns the application version
	std::string getApplicationVersion() const;

	// Sets the application version
	void setApplicationVersion(const std::string &version);

	// Runs the application
	void run();

	// Quits the application
	void quit();

private:

	CL_SetupCore                    mSetupCore;
	CL_SetupDisplay                 mSetupDisplay;
	CL_SetupGL                      mSetupGL;
	CL_SetupNetwork                 mSetupNetwork;
	CL_SetupSound                   mSetupSound;
	CL_SetupVorbis                  mSetupVorbis;

	CL_Signal_v0                    mSigInit;
	CL_Signal_v1<int>               mSigUpdate;
	CL_Signal_v0                    mSigQuit;

	std::string                     mDataDirectory;
	std::string                     mCompanyName;
	std::string                     mApplicationName;
	std::string                     mApplicationVersion;
	bool                            mQuit;

	CL_SharedPtr<Balance>           mBalance;
	CL_SharedPtr<Database>          mDatabase;
	CL_SharedPtr<ResourceManager>   mResourceManager;
	CL_SharedPtr<ResourceQueue>     mResourceQueue;
	CL_SharedPtr<Graphics>          mGraphics;
	CL_SharedPtr<Keyboard>          mKeyboard;
	CL_SharedPtr<Mouse>             mMouse;
	CL_SoundOutput                  mSoundOutput;
	CL_SharedPtr<LuaScript>         mLuaScript;
};

#endif
