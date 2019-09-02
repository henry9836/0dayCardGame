#pragma once
#include "Util.h"
#include "GameObject.h"
#include "MeshManager.h"
#include "Camera.h"
#include "Cards.h"
#include "Character.h"
#include "Bars.h"
#include "Menu.h"

class CMenu;

class Game {
public:

	Game();
	~Game();

	Scenes currentScene;
	Camera camera;
	CMenu* StartMenu;

	//scenes
	vector<GameObject*> gameObjects; //global
	vector<GameObject*> maingameObjects; //main menu
	vector<GameObject*> playgameObjects; //game

	vector<Bars*> BarsObjects;

	Character* playerOne;
	Character* playerTwo;
	Character* playerAI;
	


	glm::vec2 ScreenSize = {1000,750};
	glm::vec2 MousePosition;

	void switchScene(Scenes newScene);


	std::vector<std::string> StartOpt;
	

};

void Start(int argc, char** argv);
