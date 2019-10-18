#pragma once
#include <iostream>
#include <fmod.hpp>
#include "ConsoleController.h"

class AudioSystem {
public:

	bool AudioInit();
	void Restart();
	void Play(int track);
	void Tick();

	enum Tracks {
		BACK,
		GAMEBACK,
		SELECTBACK,
		DENY,
		SUCCESS
	};

	FMOD::System* audioSystem;
	FMOD::Sound* backMusic;
	FMOD::Sound* backGameMusic;
	FMOD::Sound* selectBackGameMusic;
	FMOD::Sound* denySound;
	FMOD::Sound* successSound;
}; 