#include "Precompiled.h"
#include "Profile.h"
#include "Application.h"

Profile::Profile(const std::string &name)
{
	mProfileDir = CL_PathHelp::add_trailing_slash(Application::getSingleton().getConfigDirectory() + name);
	mFileName = mProfileDir + Application::getSingleton().getApplicationName() + ".xml";

	try
	{
		mResourceManager = CL_ResourceManager(mFileName);
	}
	catch (const CL_Exception &)
	{
	}
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
