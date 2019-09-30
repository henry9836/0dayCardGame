#pragma once
#include "Util.h"
#include "GameObject.h"
#include "MeshManager.h"
#include "Camera.h"
#include "Cards.h"
#include "Character.h"
#include "Selection.h"
#include "Bars.h"
#include "Menu.h"

class CMenu;
class Selection;

class Game {
public:

	Game();
	~Game();

	Scenes currentScene;
	Camera camera;
	CMenu* StartMenu;
	CMenu* HowToPlayMenu;

	Selection* AddSelection;
	Selection* Player1Selection;
	Selection* Player2Selection;

	//scenes
	vector<GameObject*> gameObjects; //global
	vector<GameObject*> maingameObjects; //main menu
	vector<GameObject*> playgameObjects; //game
	vector<GameObject*> howtoplayObjects; // instructions of how to play
	vector<GameObject*> lostObjects; //lose screen
	vector<Card*> deckselectionObjects; //DeckSelection


	Character* playerOne;
	Character* playerTwo;
	Character* playerAI;
	
	int currentLvl = 1;
	bool gameover = false;

	glm::vec2 ScreenSize = {1700,1000};
	glm::vec2 MousePosition;

	void switchScene(Scenes newScene);


	std::vector<std::string> StartOpt;
	

};

void Start(int argc, char** argv);
