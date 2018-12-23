#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>
#include <glm/glm.hpp>
#include <string>

#include "Util.h"

#define FMOD_ERROR_CHECK(_result) CheckForErrors(_result, __FILE__, __LINE__)

class Audio
{
public:
	// Creates an object
	Audio();
	// Creates an object and load all data
	Audio(std::string path);

	// Load all data for the file
	NE_ERROR Init(char* file);
	// Play the audio source
	NE_ERROR Play();
	// Play audio source in 3D
	NE_ERROR Play3D(float min, float max);
	// Create a user generated sound
	NE_ERROR UserCreateSound();
	// Set the 3D Position of the player
	void Set3DPosition(float x, float y, float z);
	// Set the 3D Position of the player
	void Set3DPosition(glm::vec3 pos);
	// Pause the audio source
	NE_ERROR Pause();
	// Restart the audio source
	NE_ERROR Restart();
	// Switch from start to pause
	NE_ERROR SwitchPause();

	// Used for 3D Audio
	void Update();

	// Set the speed of the audio source
	NE_ERROR SetSpeed(float speed);
	// Set if the audio source is looped
	NE_ERROR SetLooped(bool value);

	// Get the current speed
	float GetSpeed();

	~Audio();

private:
	// Load data from file
	void LoadFileMemory(const char* name, void **buff, int* length);

	// Used for FMOD_CHECK_ERROR macro
	void CheckForErrors(FMOD_RESULT result, const char* file, int line);

	FMOD_RESULT F_CALLBACK pcmreadcallback(FMOD_SOUND* sound, void *data, unsigned int datalen);
	FMOD_RESULT F_CALLBACK pcmsetposcallback(FMOD_SOUND* sound, int subsound, unsigned int position);
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
	FMOD_MODE mode = FMOD_OPENUSER | FMOD_LOOP_NORMAL;

	bool alreadyStarted = false;
};

