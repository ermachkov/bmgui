#ifndef SOUND_H
#define SOUND_H

// Sound class
class Sound
{
public:

	// Constructor
	Sound(const std::string &name);

	// Returns true if the sound is playing now
	bool isPlaying();

	// Returns true if the playback is paused
	bool isPaused() const;

	// Plays the sound
	void play();

	// Pauses the sound
	void pause();

	// Stops the sound
	void stop();

private:

	CL_SoundBuffer_Session  mSession;
	bool                    mPaused;
};

#endif
