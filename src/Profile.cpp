#include "Precompiled.h"
#include "Profile.h"
#include "Application.h"

Profile::Profile(const std::string &name)
{
	mProfileDir = CL_PathHelp::add_trailing_slash(Application::getSingleton().getConfigDirectory() + name);
	mFileName = mProfileDir + Application::getSingleton().getApplicationName() + ".xml";

	// load user config file
	bool exists = true;
	try
	{
		mResourceManager = CL_ResourceManager(mFileName);
	}
	catch (const CL_Exception &)
	{
		exists = false;
	}

	// load system config file
	CL_ResourceManager resources;
	try
	{
		resources = CL_ResourceManager("/etc/bmgui.xml");
	}
	catch (const CL_Exception &)
	{
	}

	// initialize command line parameters
	Application &app = Application::getSingleton();
	if (app.mGateway.empty())
		app.mGateway = getString("gateway", resources.get_string_resource("gateway", "127.0.0.1"));
	if (app.mLocalAddr.empty())
		app.mLocalAddr = getString("local_addr", resources.get_string_resource("local_addr", "127.0.0.1"));
	if (app.mNetmask.empty())
		app.mNetmask = getString("netmask", resources.get_string_resource("netmask", "255.255.255.0"));
	if (app.mDNS.empty())
		app.mDNS = getString("dns", resources.get_string_resource("dns", "127.0.0.1"));
	if (app.mInputDev.empty())
		app.mInputDev = getString("input_dev", resources.get_string_resource("input_dev", "1"));
	if (app.mServerStatus.empty())
		app.mServerStatus = getString("server_status", resources.get_string_resource("server_status", "true"));
	if (app.mAvailableUpdateVersion.empty())
		app.mAvailableUpdateVersion = getString("available_update_version", resources.get_string_resource("available_update_version", ""));

	setString("gateway", app.mGateway);
	setString("local_addr", app.mLocalAddr);
	setString("netmask", app.mNetmask);
	setString("dns", app.mDNS);
	setInt("input_dev", CL_StringHelp::text_to_int(app.mInputDev));
	setBool("server_status", CL_StringHelp::text_to_bool(app.mServerStatus));
	setString("available_update_version", app.mAvailableUpdateVersion);

	// initialize normal configuration options
	if (getString("server_addr").empty())
		setString("server_addr", resources.get_string_resource("server_addr", "192.168.0.1"));
	if (getString("remote_control").empty())
		setBool("remote_control", resources.get_boolean_resource("remote_control", true));
	if (getString("ignored_update_version").empty())
		setString("ignored_update_version", resources.get_string_resource("ignored_update_version", ""));
	if (getString("cal_command").empty())
		setString("cal_command", resources.get_string_resource("cal_command", "sudo bmgui_xinput_calibrator"));
	if (getString("language").empty())
		setInt("language", resources.get_integer_resource("language", 1));
	if (getString("fullscreen").empty())
		setBool("fullscreen", resources.get_boolean_resource("fullscreen", true));
	if (getString("width").empty())
		setInt("width", resources.get_integer_resource("width", 1024));
	if (getString("height").empty())
		setInt("height", resources.get_integer_resource("height", 768));

	// save the user profile if needed
	if (!exists)
		save();
}

bool Profile::save()
{
	try
	{
		CL_Directory::create(mProfileDir, true);
		mResourceManager.save(mFileName);
		system("sync");
	}
	catch (const CL_Exception &)
	{
		return false;
	}

	return true;
}

std::string Profile::getString(const std::string &name, const std::string &defaultValue)
{
	return mResourceManager.get_string_resource(name, defaultValue);
}

void Profile::setString(const std::string &name, const std::string &value)
{
	CL_Resource resource = mResourceManager.resource_exists(name) ? mResourceManager.get_resource(name) : mResourceManager.create_resource(name, "option");
	resource.get_element().set_attribute("value", value);
}

int Profile::getInt(const std::string &name, int defaultValue)
{
	return mResourceManager.get_integer_resource(name, defaultValue);
}

void Profile::setInt(const std::string &name, int value)
{
	CL_Resource resource = mResourceManager.resource_exists(name) ? mResourceManager.get_resource(name) : mResourceManager.create_resource(name, "option");
	resource.get_element().set_attribute("value", CL_StringHelp::int_to_text(value));
}

bool Profile::getBool(const std::string &name, bool defaultValue)
{
	return mResourceManager.get_boolean_resource(name, defaultValue);
}

void Profile::setBool(const std::string &name, bool value)
{
	CL_Resource resource = mResourceManager.resource_exists(name) ? mResourceManager.get_resource(name) : mResourceManager.create_resource(name, "option");
	resource.get_element().set_attribute("value", CL_StringHelp::bool_to_text(value));
}
