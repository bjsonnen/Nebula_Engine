#include "Audio.h"

// remove compiler warnings for fopen();
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

NE::Audio::Audio()
{
	result = FMOD::System_Create(&system);
	FMOD_ERROR_CHECK(result);
	result = system->getVersion(&version);
	FMOD_ERROR_CHECK(result);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	FMOD_ERROR_CHECK(result);
}

NE::Audio::Audio(std::string path)
{
	result = FMOD::System_Create(&system);
	FMOD_ERROR_CHECK(result);
	result = system->getVersion(&version);
	FMOD_ERROR_CHECK(result);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	FMOD_ERROR_CHECK(result);

	LoadFileMemory(path.c_str(), &buff, &length);
	memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.length = length;

	result = system->createSound((const char *)buff, FMOD_OPENMEMORY | FMOD_LOOP_OFF, &exinfo, &sound);
	FMOD_ERROR_CHECK(result);
	free(buff);
}

void NE::Audio::Init()
{
	result = FMOD::System_Create(&system);
	FMOD_ERROR_CHECK(result);
	result = system->getVersion(&version);
	FMOD_ERROR_CHECK(result);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	FMOD_ERROR_CHECK(result);
}

void NE::Audio::Update()
{
}

NE_ERROR NE::Audio::Init(char* file)
{
	LoadFileMemory(file, &buff, &length);
	memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.length = length;

	result = system->createSound((const char *)buff, FMOD_OPENMEMORY | FMOD_LOOP_OFF, &exinfo, &sound);
	FMOD_ERROR_CHECK(result);
	free(buff);
	return NE_OK;
}

NE_ERROR NE::Audio::Play()
{
	if (!alreadyStarted)
	{
		result = system->playSound(sound, 0, false, &channel);
		FMOD_ERROR_CHECK(result);
		alreadyStarted = true;
	}
	if (result == FMOD_OK)
		return NE_OK;
	else
		return NE_FALSE;
}

NE_ERROR NE::Audio::Play3D(float min, float max)
{
	if (!alreadyStarted)
	{
		result = system->set3DSettings(1.0f, 1.0f, 1.0f);
		FMOD_ERROR_CHECK(result);
		// Sound already created!
		result = sound->set3DMinMaxDistance(min, max);
		FMOD_ERROR_CHECK(result);
		result = sound->setMode(FMOD_LOOP_NORMAL);
		FMOD_ERROR_CHECK(result);

		result = system->playSound(sound, 0, false, &channel);
		FMOD_ERROR_CHECK(result);
		alreadyStarted = true;
	}
	return NE_OK;
}

NE_ERROR NE::Audio::UserCreateSound()
{
	memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.numchannels = 0;
	exinfo.defaultfrequency = 44100;
	exinfo.decodebuffersize = 44100;
	exinfo.length = exinfo.defaultfrequency * sizeof(signed short) * 5;
	exinfo.format = FMOD_SOUND_FORMAT_PCM16;
	// ToDo pcmreadcallback & pcmsetposcallback

	result = system->createSound(0, mode, &exinfo, &sound);
	FMOD_ERROR_CHECK(result);

	result = system->playSound(sound, 0, false, &channel);
	FMOD_ERROR_CHECK(result);

	return NE_OK;
}

void NE::Audio::Set3DPosition(float x, float y, float z)
{
	FMOD_VECTOR pos = {x, y, z};
	FMOD_VECTOR vel = {0.0f, 0.0f, 0.0f};

	result = channel->set3DAttributes(&pos, &vel);
	FMOD_ERROR_CHECK(result);
	result = channel->setPaused(false);
	FMOD_ERROR_CHECK(result);
}

void NE::Audio::Set3DPosition(glm::vec3 pos)
{
	FMOD_VECTOR fmod_pos = { pos.x, pos.y, pos.z };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

	result = channel->set3DAttributes(&fmod_pos, &vel);
	FMOD_ERROR_CHECK(result);
	result = channel->setPaused(false);
	FMOD_ERROR_CHECK(result);
}

void NE::Audio::Set3DPosition(NE::Vector3 pos)
{
	FMOD_VECTOR fmod_pos = { pos.x, pos.y, pos.z };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

	result = channel->set3DAttributes(&fmod_pos, &vel);
	FMOD_ERROR_CHECK(result);
	result = channel->setPaused(false);
	FMOD_ERROR_CHECK(result);
}

NE_ERROR NE::Audio::Pause()
{
	result = channel->setPaused(true);
	FMOD_ERROR_CHECK(result);
	return NE_OK;
}

NE_ERROR NE::Audio::Restart()
{
	result = channel->setPaused(false);
	FMOD_ERROR_CHECK(result);
	return NE_OK;
}

NE_ERROR NE::Audio::SwitchPause()
{
	bool tmp;
	result = channel->getPaused(&tmp);
	FMOD_ERROR_CHECK(result);
	result = channel->setPaused(tmp);
	FMOD_ERROR_CHECK(result);
	return NE_OK;
}

void NE::Audio::UpdateAudio()
{
	result = system->update();
	FMOD_ERROR_CHECK(result);
}

NE_ERROR NE::Audio::Release()
{
	if (!sound || !system)
		return NE_FALSE;

	if (sound)
		result = sound->release();
	FMOD_ERROR_CHECK(result);
	if (system)
		result = system->close();
	FMOD_ERROR_CHECK(result);
	result = system->release();
	FMOD_ERROR_CHECK(result);
	return NE_OK;
}

NE_ERROR NE::Audio::SetSpeed(float speed)
{
	float tmp;
	result = sound->setMusicSpeed(speed);
	FMOD_ERROR_CHECK(result);
	result = sound->getMusicSpeed(&tmp);
	if (speed != tmp)
		return NE_FALSE;
	else
		return NE_OK;
}

NE_ERROR NE::Audio::SetLooped(bool value)
{
	int i = value ? 1 : 0;
	result = sound->setLoopCount(i);
	FMOD_ERROR_CHECK(result);
	return NE_OK;
}

float NE::Audio::GetSpeed()
{
	float tmp;
	result = sound->getMusicSpeed(&tmp);
	FMOD_ERROR_CHECK(result);
	return tmp;
}

NE::Audio::~Audio()
{
	if(sound)
		result = sound->release();
	FMOD_ERROR_CHECK(result);
	if(system)
		result = system->close();
	FMOD_ERROR_CHECK(result);
	result = system->release();
	FMOD_ERROR_CHECK(result);
}

void NE::Audio::LoadFileMemory(const char * name, void ** buff, int * length)
{
	FILE *file = NULL;
	file = fopen(name, "rb");

	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	fseek(file, 0, SEEK_SET);

	void *mem = malloc(len);
	fread(mem, 1, len, file);

	fclose(file);

	*buff = mem;
	*length = len;
}

void NE::Audio::CheckForErrors(FMOD_RESULT result, const char * file, int line)
{
	if (result != FMOD_OK)
	{
		printf("%s(%d): FMOD error %d - %s\n", file, line, result, FMOD_ErrorString(result));
	}
}

FMOD_RESULT F_CALLBACK NE::Audio::pcmreadcallback(FMOD_SOUND * sound, void * data, unsigned int datalen)
{
	static float  t1 = 0, t2 = 0;        // time
	static float  v1 = 0, v2 = 0;        // velocity
	signed short *stereo16bitbuffer = (signed short *)data;

	for (unsigned int count = 0; count < (datalen >> 2); count++)     // >>2 = 16bit stereo (4 bytes per sample)
	{
		*stereo16bitbuffer++ = (signed short)(sin(t1) * 32767.0f);    // left channel
		*stereo16bitbuffer++ = (signed short)(sin(t2) * 32767.0f);    // right channel

		t1 += 0.01f + v1;
		t2 += 0.0142f + v2;
		v1 += (float)(sin(t1) * 0.002f);
		v2 += (float)(sin(t2) * 0.002f);
	}

	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK NE::Audio::pcmsetposcallback(FMOD_SOUND * sound, int subsound, unsigned int position)
{
	return FMOD_OK;
}
