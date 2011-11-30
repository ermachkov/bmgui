#ifndef SOUND_RESOURCE_H
#define SOUND_RESOURCE_H

#include "Resource.h"

// Sound resource class
class SoundResource : public Resource
{
public:

	// Constructor
	SoundResource(CL_Resource &resource);

	// Returns a list of resource dependencies
	virtual std::vector<std::string> getDependencies() const;

	// Returns a list of resource files
	virtual std::vector<std::string> getFileNames() const;

	// Returns true if the resource is loaded
	virtual bool isLoaded() const;

	// Loads the resource
	virtual void load();

	// Loads data file in the background thread
	virtual void loadInBackgroundThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource);

	// Loads data file in the main thread
	virtual void loadInMainThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource);

	// Returns the sound buffer
	CL_SoundBuffer getSoundBuffer() const;

private:

	CL_Resource     mResource;
	CL_SoundBuffer  mSoundBuffer;
	std::string     mFileName;
};

#endif
