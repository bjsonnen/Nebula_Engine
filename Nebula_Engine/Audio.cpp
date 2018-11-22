#include "Audio.h"

Audio::Audio(std::string path)
{
	result = FMOD::System_Create(&system);
	system->getVersion(&version);

	system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	LoadFileMemory(path.c_str(), &buff, &length);
	memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.length = length;

	result = system->createSound((const char *)buff, FMOD_OPENMEMORY | FMOD_LOOP_OFF, &exinfo, &sound);
	free(buff);
}

bool Audio::Play()
{
	if (!alreadyStarted)
	{
		result = system->playSound(sound, 0, false, &channel);
		alreadyStarted = true;
	}
	if (result == FMOD_OK)
		return true;
	else
		return false;
}

bool Audio::Pause()
{
	return false;
}

bool Audio::Restart()
{
	return false;
}

bool Audio::SwitchPause()
{
	return false;
}

void Audio::Update()
{
	system->update();
}

bool Audio::SetSpeed(float speed)
{
	
	float tmp;
	sound->setMusicSpeed(speed);
	sound->getMusicSpeed(&tmp);
	if (speed != tmp)
		return false;
	else
		return true;
}

bool Audio::SetLooped(bool value)
{
	int i = value ? 1 : 0;
	sound->setLoopCount(i);
	return true;
}

float Audio::GetSpeed()
{
	float tmp;
	sound->getMusicSpeed(&tmp);
	return tmp;

}

Audio::~Audio()
{
	sound->release();
	system->close();
	system->release();
}

void Audio::LoadFileMemory(const char * name, void ** buff, int * length)
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
