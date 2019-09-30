#pragma once
#include <iostream>
#include <fmod.hpp>
#include "ConsoleController.h"

class AudioSystem {
public:

	bool AudioInit();
	void Play(int track);
	void Tick();

	enum Tracks {
		BACK
	};

	FMOD::System* audioSystem;
	FMOD::Sound* backMusic;
};