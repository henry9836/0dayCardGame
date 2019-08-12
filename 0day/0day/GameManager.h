#pragma once
#include "Util.h"
#include "GameObject.h"

class Game {
public:

	Game();
	~Game();

	Scenes currentScene;
	vector<GameObject*> gameObjects;
	glm::vec2 ScreenSize = {750	,750};
	glm::vec2 MousePosition;

	void switchScene(Scenes newScene);
};

void Start(int argc, char** argv);
