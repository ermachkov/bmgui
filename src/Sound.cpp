#include "Precompiled.h"
#include "Sound.h"
#include "ResourceManager.h"
#include "SoundResource.h"

Sound::Sound(const std::string &name)
: mPaused(false)
{
	CL_SharedPtr<SoundResource> resource = cl_dynamic_pointer_cast<SoundResource>(ResourceManager::getSingleton().getResource(name));
	if (!resource)
		throw Exception(cl_format("Resource '%1' is not a sound resource", name));
	if (!resource->isLoaded())
		throw Exception(cl_format("Sound '%1' is not loaded", name));

	mSession = resource->getSoundBuffer().prepare();
}

bool Sound::isPlaying()
{
	return mSession.is_playing();
}

bool Sound::isPaused() const
{
	return mPaused;
}

void Sound::play()
{
	if (!mSession.is_playing() && !mPaused)
		mSession.set_position(0);
	mSession.play();
	mPaused = false;
}

void Sound::pause()
{
	mSession.stop();
	mPaused = true;
}

void Sound::stop()
{
	mSession.stop();
	mSession.set_position(0);
	mPaused = false;
}
