#pragma once
#include "Util.h"
#include "GameObject.h"

class Game {
public:

	Game();
	~Game();

	Scenes currentScene;
	vector<GameObject>* gameObjects;

	void switchScene(Scenes newScene);
};

void Start();