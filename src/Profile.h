#ifndef PROFILE_H
#define PROFILE_H

class Profile
{
public:

	Profile(const std::string &name);

	bool save();

	std::string getString(const std::string &name, const std::string &defaultValue = "");

	void setString(const std::string &name, const std::string &value);

	int getInt(const std::string &name, int defaultValue = 0);

	void setInt(const std::string &name, int value);

	bool getBool(const std::string &name, bool defaultValue = false);

	void setBool(const std::string &name, bool value);

private:

	std::string         mProfileDir;
	std::string         mFileName;
	CL_ResourceManager  mResourceManager;
};

#endif
