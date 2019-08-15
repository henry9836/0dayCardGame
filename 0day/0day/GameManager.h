#pragma once
#include "Util.h"
#include "GameObject.h"
#include "MeshManager.h"

class Game {
public:

	Game();
	~Game();

	Scenes currentScene;
	
	//scenes
	vector<GameObject*> gameObjects; //global
	vector<GameObject*> maingameObjects; //main menu
	vector<GameObject*> playgameObjects; //game
	
	glm::vec2 ScreenSize = {1000,750};
	glm::vec2 MousePosition;

	void switchScene(Scenes newScene);

private:

};

void Start(int argc, char** argv);
