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
#include "Audio.h"

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
	
	//Game Scene
	GameObject* p1DeckVisual;
	GameObject* p1GYVisual;
	GameObject* p2DeckVisual;
	GameObject* p2GYVisual;
	GameObject* gameBackground;
	GameObject* background;
	GameObject* Page2;

	//Effects
	GameObject* p1EffectLines;
	GameObject* p1EffectStopped;

	GameObject* p2EffectLines;
	GameObject* p2EffectStopped;

	GameObject* aiEffectLines;
	GameObject* aiEffectStopped;


	Character* playerOne;
	Character* playerTwo;
	Character* playerAI;
	
	CTextLabel* levelText;

	int currentLvl = 1;
	bool isSecondPage = false;
	bool gameover = false;
	bool once = false;
	bool Selectonce = false;
	bool Gameonce = false;

	glm::vec2 ScreenSize = {1700,1000};
	glm::vec2 MousePosition;

	glm::vec3 p1EffectPos;
	glm::vec3 p2EffectPos;
	glm::vec3 aiEffectPos;

	void switchScene(Scenes newScene);


	std::vector<std::string> StartOpt;
	

};

void Start(int argc, char** argv);
