#include "Audio.h"

bool AudioSystem::AudioInit()
{

	Console_OutputLog(L"Initalizing Audio...", LOGINFO);

	FMOD_RESULT result;
	result = FMOD::System_Create(&audioSystem);
	if (result != FMOD_OK) {
		Console_OutputLog(L"Cannot Initalise Audio FMOD_OK Check Failed!", LOGWARN);
		return false;
	}
	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK) {
		Console_OutputLog(L"Cannot Initalise Audio FMOD_OK Check Failed!", LOGWARN);
		return false;
	}

	/* CREATE SOUNDS */

	result = audioSystem->createSound("Resources/Sounds/Menu.mp3", FMOD_LOOP_NORMAL, 0, &backMusic);
	if (result != FMOD_OK) {
		Console_OutputLog(L"Cannot Initalise Audio Track Menu.mp3", LOGWARN);
	}

	result = audioSystem->createSound("Resources/Sounds/Game.mp3", FMOD_LOOP_NORMAL, 0, &backGameMusic);
	if (result != FMOD_OK) {
		Console_OutputLog(L"Cannot Initalise Audio Track Game.mp3", LOGWARN);
	}

	result = audioSystem->createSound("Resources/Sounds/error.wav", FMOD_DEFAULT, 0, &denySound);
	if (result != FMOD_OK) {
		Console_OutputLog(L"Cannot Initalise Audio Track error.wav", LOGWARN);
	}

	result = audioSystem->createSound("Resources/Sounds/success.wav", FMOD_DEFAULT, 0, &successSound);
	if (result != FMOD_OK) {
		Console_OutputLog(L"Cannot Initalise Audio Track success.wav", LOGWARN);
	}

	Console_OutputLog(L"Initalized Audio...", LOGINFO);

	return true;
}

void AudioSystem::Restart() {
	audioSystem->release();
	AudioInit();
}

void AudioSystem::Play(int track) {
	bool foundtrack = true;
	bool result = false;
	switch (track)
	{
	case BACK: {
		result = audioSystem->playSound(backMusic, 0, false, 0);
		break;
	}
	case GAMEBACK: {
		result = audioSystem->playSound(backGameMusic, 0, false, 0);
		break;
	}
	case SELECTBACK: {
		result = audioSystem->playSound(selectBackGameMusic, 0, false, 0);
		break;
	}
	case DENY: {
		result = audioSystem->playSound(denySound, 0, false, 0);
		break;
	}
	case SUCCESS: {
		result = audioSystem->playSound(successSound, 0, false, 0);
		break;
	}
	default: {
		foundtrack = false;
		Console_OutputLog(to_wstring("Audio Track: " + std::to_string(track) + " was called but it doesn't exist"), LOGWARN);
		break;
	}
	}

	if (foundtrack) {
		if (result != FMOD_OK) {
			Console_OutputLog(to_wstring("Audio Track: " + std::to_string(track) + " was called but cannot be played"), LOGWARN);
			return;
		}
	}
}

void AudioSystem::Tick()
{
	audioSystem->update();
}

