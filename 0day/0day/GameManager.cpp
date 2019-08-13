#include "GameManager.h"

Game game;

bool DEBUG_MODE = true;

void Start()
{
	

	Console_OutputLog(L"Initialising OpenGL Components...", LOGINFO);


}

Game::Game()
{
	Console_OutputLog(L"Constructing Game Class", LOGINFO);
}

Game::~Game()
{
	Console_OutputLog(L"Deconstructing Game Class", LOGINFO);
}

void Game::switchScene(Scenes newScene)
{
	this->currentScene = newScene;
}
