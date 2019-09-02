#include "GameManager.h"

Game* game;

bool mouseDown = false;
float currentTime;
float deltaTime;
float pasttime;

void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//Render Objects

	for (size_t i = 0; i < game->gameObjects.size(); i++) 
	{
		game->gameObjects.at(i)->Render();
	}

	//Render Based On Current Scene

	if (game->currentScene == Scenes::SCENE_MAIN) {
		game->StartMenu->Render();
		for (size_t i = 0; i < game->maingameObjects.size(); i++)
		{
			game->maingameObjects.at(i)->Render();
		}
	}
	else if (game->currentScene == Scenes::SCENE_GAME) {
		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Render();
		}
	}

	glutSwapBuffers();
}

//Update Loop
void Update() {

	currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - pasttime) * 0.1f;
	pasttime = currentTime;

	//Tick Objects

	game->camera.Tick(game->ScreenSize, deltaTime);
	for (size_t i = 0; i < game->gameObjects.size(); i++)
	{
		game->gameObjects.at(i)->Tick(deltaTime);
	}

	//Tick Based On Current Scene

	if (game->currentScene == Scenes::SCENE_MAIN) {
		int tempOutput = NULL;
		game->StartMenu->Process(tempOutput);
		CInputManager::ProcessKeyInput();
		switch (tempOutput)
		{
		case 0:
			game->currentScene = Scenes::SCENE_GAME;
			break;
		case 1:
			game->currentScene = Scenes::SCENE_MAIN;
			break;
		case 2:
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
		for (size_t i = 0; i < game->maingameObjects.size(); i++)
		{
			game->maingameObjects.at(i)->Tick(deltaTime);
		}
	}
	else if (game->currentScene == Scenes::SCENE_GAME) {
		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Tick(deltaTime);
		}
	}

	Render();
}

void mouseMovement(int x, int y) {
	float aX = (float(x) - (game->ScreenSize.x / 2)) / (game->ScreenSize.x / 2);
	float aY = (float(y) - (game->ScreenSize.y / 2)) / (game->ScreenSize.y / 2);
	//wcout << L"Adjusted X:" << aX << L" Y:" << aY << endl;
	game->MousePosition = { aX, aY };
}

void mouse(int button, int state, int x, int y) { //Click
	if (!mouseDown) {
		wcout << "Mouse Clicked: " << button << endl;
		mouseDown = true;
	}
	else {
		mouseDown = false;
	}
}

void DealCardsRandom(Character* _char) {
	Console_OutputLog(L"Dealing Cards...", LOGINFO);
	for (size_t i = 0; i < 12; i++)
	{
		int choice = rand() % 3;
		switch (choice)
		{
		case 0: { //red ring
			_char->Hand.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/REDRINGCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(_char->handPos, glm::vec3(0, 0, 0), glm::vec3(80.0f, 100.0f, 1.0f)), "Red Ring Of Death Card", 50, 50, AttackCard::REDCIRCLE));
			break;
		}
		case 1: { //DDOS
			_char->Hand.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/DDOSCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(_char->handPos, glm::vec3(0, 0, 0), glm::vec3(80.0f, 100.0f, 1.0f)), "DDOS Card", 70, 75, AttackCard::DDOS));
			break;
		}
		case 2: { //SQL
			_char->Hand.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/SQLCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(_char->handPos, glm::vec3(0, 0, 0), glm::vec3(80.0f, 100.0f, 1.0f)), "SQL Card", 30, 10, AttackCard::SQL));
			break;
		}
		default: {
			i--;
			Console_OutputLog(L"Choice out of bounds retrying...", LOGWARN);
			break;
		}
		}
	}
}

void populateGameObjectList() {
	Console_OutputLog(L"Creating Players...", LOGINFO);
	game->playerOne = new Human();
	game->playerTwo = new Human();
	game->playerAI = new AI(1);
	
	Console_OutputLog(L"Creating GameObjects...", LOGINFO);

	//GLOBALS

	//MAINMENU OBJECTS

#pragma region StartMenu
	std::vector<std::string> StartOpt;
	StartOpt.push_back("Start");
	StartOpt.push_back("Options");
	StartOpt.push_back("Quit");
	game->StartMenu = new CMenu(StartOpt, glm::vec2(0.0f, 0.0f), game);
#pragma endregion

	//game->maingameObjects.push_back(new GameObject(new RenderText(new CTextLabel("Main Menu\n 1. Main Menu\n 2. Play", "Resources/Fonts/TerminusTTF-4.47.0.ttf", glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, "Main Menu Text")),new IdleTick, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f)), "Main Menu Text"));

	//GAMEPLAY OBJECTS
	game->playgameObjects.push_back(game->playerOne);
	game->playgameObjects.push_back(game->playerTwo);
	game->playgameObjects.push_back(game->playerAI);

	//SET HANDPOSITIONS FOR PLAYERS

	game->playerOne->handPos = glm::vec3(-300,-250,0);
	game->playerTwo->handPos = glm::vec3(0, -250, 0);
	game->playerAI->handPos = glm::vec3(-300, 250, 0);

	//DEAL CARDS
	DealCardsRandom(game->playerOne);
	DealCardsRandom(game->playerTwo);
	DealCardsRandom(game->playerAI);
	
}

void Exit()
{
	Console_OutputLog(L"Exiting Game...", LOGINFO);

	for (size_t i = 0; i < game->gameObjects.size(); i++)
	{
		game->gameObjects.at(i)->~GameObject();
		game->gameObjects.erase(game->gameObjects.begin() + i);
		i--;
	}

	for (size_t i = 0; i < game->playgameObjects.size(); i++)
	{
		game->playgameObjects.at(i)->~GameObject();
		game->playgameObjects.erase(game->playgameObjects.begin() + i);
		i--;
	}

	for (size_t i = 0; i < game->maingameObjects.size(); i++)
	{
		game->maingameObjects.at(i)->~GameObject();
		game->maingameObjects.erase(game->maingameObjects.begin() + i);
		i--;
	}

	game->~Game();
	delete game;
	game = nullptr;
	exit(0);
}

void Start(int argc, char** argv)
{
	//Init OpenGL
	game = new Game;

	Console_OutputLog(L"Initialising OpenGL Components...", LOGINFO);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize((int)game->ScreenSize.x, (int)game->ScreenSize.y);

	glutCreateWindow("0day");

	if (glewInit() != GLEW_OK) {
		Console_OutputLog(L"Glew INIT FAILED! The program cannot recover from this error", LOGFATAL);
		system("pause");
		exit(0);
	}

	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 0.0, 1.0);
	MeshManager::GetInstance();
	CInputManager::CInputManager();
	//create GameObjects
	game->camera.initializeCamera();
	game->camera.SwitchMode(Camera::ORTH, glm::vec3(0,0,0), glm::vec3(0,0,-2), glm::vec3(0,0,0), 2.0f, 0.0f);
	populateGameObjectList();
	//Start MeshManager


	//Start OpenGL

	Console_OutputLog(L"OpenGL Service Starting...", LOGINFO);

 	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	// mouse event handlers
	glutMainLoop();

	glutCloseFunc(Exit);

}

Game::Game()
{
	Console_OutputLog(L"Constructing Game Class", LOGINFO);
	this->currentScene = Scenes::SCENE_MAIN;
}

Game::~Game()
{
	Console_OutputLog(L"Deconstructing Game Class", LOGINFO);
	delete StartMenu;
	StartMenu = nullptr;
}

void Game::switchScene(Scenes newScene)
{
	this->currentScene = newScene;
}

