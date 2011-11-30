#include "Precompiled.h"
#include "SoundResource.h"
#include "GameAssert.h"

SoundResource::SoundResource(CL_Resource &resource)
: mResource(resource)
{
	GAME_ASSERT(mResource.get_type() == "sample");

	CL_String fileName = mResource.get_element().get_attribute("file");
	if (fileName.empty())
		throw Exception(cl_format("Sound '%1' has empty or missing 'file' attribute", mResource.get_name()));
	mFileName = mResource.get_manager().get_directory(mResource).get_file_system().get_path() + fileName;
}

std::vector<std::string> SoundResource::getDependencies() const
{
	return std::vector<std::string>();
}

std::vector<std::string> SoundResource::getFileNames() const
{
	return std::vector<std::string>(1, mFileName);
}

bool SoundResource::isLoaded() const
{
	return !mSoundBuffer.is_null();
}

void SoundResource::load()
{
	if (mSoundBuffer.is_null())
	{
		CL_ResourceManager manager = mResource.get_manager();
		mSoundBuffer = CL_SoundBuffer(mResource.get_name(), &manager);
	}
}

void SoundResource::loadInBackgroundThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource)
{
}

void SoundResource::loadInMainThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource)
{
}

CL_SoundBuffer SoundResource::getSoundBuffer() const
{
	return mSoundBuffer;
}
