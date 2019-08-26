#pragma once
#include "Util.h"
#include "GameObject.h"
#include "MeshManager.h"
#include "TextManager.h" 
#include "Camera.h"
#include "Cards.h"
#include "Character.h"

class Game {
public:

	Game();
	~Game();

	Scenes currentScene;
	Camera camera;
	//scenes
	vector<GameObject*> gameObjects; //global
	vector<GameObject*> maingameObjects; //main menu
	vector<GameObject*> playgameObjects; //game

	Character* playerOne;
	Character* playerTwo;
	Character* playerAI;
	


	glm::vec2 ScreenSize = {1000,750};
	glm::vec2 MousePosition;

	void switchScene(Scenes newScene);

private:

};

void Start(int argc, char** argv);
