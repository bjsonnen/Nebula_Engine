#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>
#include <glm/glm.hpp>
#include <string>

#include "Util.h"
#include "ECManager.h"

//! FMOD internal error check
#define FMOD_ERROR_CHECK(_result) CheckForErrors(_result, __FILE__, __LINE__)

//! Audio main class, Entity-Component-System sub-class
class Audio : public Component
{
public:
	//! Creates an object
	Audio();
	//! Creates an object and load all data
	Audio(std::string path);

	//! Used by the Entity-Component-System
	//!
	void Init() override;
	//! Used by the Entity-Component-System
	//!
	void Update() override;

	//! Load all data for the file
	//! @param file Location to the file
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR Init(char* file);
	//! Play the audio source
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR Play();
	//! Play audio source in 3D
	//! @param min Min distance
	//! @param max Max distance
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR Play3D(float min, float max);
	//! Create a user generated sound
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR UserCreateSound();
	//! Set the 3D Position of the player
	//! @param x Set current x position
	//! @param y Set current y position
	//! @param z Set current z position
	void Set3DPosition(float x, float y, float z);
	//! Set the 3D Position of the player
	//! @param pos Set current position as glm::vec3
	void Set3DPosition(glm::vec3 pos);
	//! Set the 3D Position of the player
	//! @param pos Set current position as Vector3
	//! @see Vector3
	void Set3DPosition(Vector3 pos);
	//! Pause the audio source
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR Pause();
	//! Restart the audio source
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR Restart();
	//! Switch from start to pause
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR SwitchPause();

	//! Used for 3D Audio
	void UpdateAudio();

	//! Release and clear the memory used to hold the audio files
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR Release();

	//! Set the speed of the audio source
	//! @param speed Set the speed of the sound
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR SetSpeed(float speed);
	//! Set if the audio source is looped
	// @param value Set if the audio is looped
	//! @return Returns an NE_ERROR
	//! @see NE_ERROR_CHECK
	NE_ERROR SetLooped(bool value);

	//! Get the current speed
	//! @param Returns the current speed as float
	float GetSpeed();

	~Audio();

private:
	//! Load data from file
	void LoadFileMemory(const char* name, void **buff, int* length);

	//! Used for FMOD_CHECK_ERROR macro
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

