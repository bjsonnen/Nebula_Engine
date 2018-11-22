#pragma once

#include <fmod.hpp>
#include <glm/glm.hpp>
#include <string>

class Audio
{
public:
	// Creates an object and load all data
	Audio(std::string path);

	// Play the audio source
	bool Play();
	// Play audio source in 3D
	bool Play3D(float min, float max);
	// Pause the audio source
	bool Pause();
	// Restart the audio source
	bool Restart();
	// Switch from start to pause
	bool SwitchPause();

	// Used for 3D Audio
	void Update();

	// Set the speed of the audio source
	bool SetSpeed(float speed);
	// Set if the audio source is looped
	bool SetLooped(bool value);

	// Get the current speed
	float GetSpeed();

	~Audio();

private:
	// Load data from file
	void LoadFileMemory(const char* name, void **buff, int* length);

private:
	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	unsigned int version;
	void* extradriverdata = 0;
	void* buff = 0;
	int length = 0;
	FMOD_CREATESOUNDEXINFO exinfo;

	bool alreadyStarted = false;
};

