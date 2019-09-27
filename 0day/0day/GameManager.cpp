#include "GameManager.h"

Game* game;

bool mouseDown = false;
float currentTime;
float deltaTime;
float pasttime;


void DeckSelectionInit()
{
	//All player cards in the game get push in here.
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::RedRing.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Red Ring Of Death Card", 50, 50, AttackCard::REDCIRCLE));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::DDOS.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "DDOS Card", 70, 75, AttackCard::DDOS));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::SQL.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "SQL Card", 30, 10, AttackCard::SQL));

	game->AddSelection = new Selection(game->deckselectionObjects, glm::vec3(game->ScreenSize.x * - 0.15f, game->ScreenSize.y * 0.4f, 0.0f), 4, 0.1f, 0.2f, game, 0, true, true);
	game->Player1Selection = new Selection(game->playerOne->cardPile->Deck, glm::vec3(game->ScreenSize.x * -0.45f, game->ScreenSize.y * 0.4f, 0.0f), 3, 0.09f, 0.17f, game, 1, false, false);
	game->Player2Selection = new Selection(game->playerTwo->cardPile->Deck, glm::vec3(game->ScreenSize.x * 0.25f, game->ScreenSize.y * 0.4f, 0.0f), 3, 0.09f, 0.17f, game, 2, false, false);
}

void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//Render Objects

	for (size_t i = 0; i < game->gameObjects.size(); i++) 
	{
		game->gameObjects.at(i)->Render();
	}

	//Render Based On Current Scene
	switch (game->currentScene)
	{
	case Scenes::SCENE_MAIN:
	{
		game->StartMenu->Render();
		for (size_t i = 0; i < game->maingameObjects.size(); i++)
		{
			game->maingameObjects.at(i)->Render();
		}
		break;
	}
	case Scenes::SCENE_SELECTION:
	{
		game->AddSelection->Render();
		game->Player1Selection->Render();
		game->Player2Selection->Render();
		break;
	}
	case Scenes::SCENE_GAME:
	{
		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Render();
		}
		break;
	}
	default:
		break;
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
		game->gameObjects.at(i)->Tick(deltaTime, game->gameObjects.at(i));
	}

	//Tick Based On Current Scene

	switch (game->currentScene)
	{
	case Scenes::SCENE_MAIN:
	{
		int tempOutput = NULL;
		game->StartMenu->Process(tempOutput);
		CInputManager::ProcessKeyInput();
		switch (tempOutput)
		{
		case 0:
			game->currentScene = Scenes::SCENE_SELECTION;
			DeckSelectionInit();
			break;
		case 1:
			game->currentScene = Scenes::SCENE_MAIN; // Would be option screen
			break;
		case 2:
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
		for (size_t i = 0; i < game->maingameObjects.size(); i++)
		{
			game->maingameObjects.at(i)->Tick(deltaTime, game->maingameObjects.at(i));
		}
		break;
	}
	case Scenes::SCENE_SELECTION:
	{
		game->AddSelection->Process(game->playerOne, game->playerTwo);
		game->Player1Selection->Process(game->playerOne, game->playerTwo);
		game->Player2Selection->Process(game->playerOne, game->playerTwo);
		CInputManager::ProcessKeyInput();
		break;
	}
	case Scenes::SCENE_GAME:
	{
		Console_OutputLog(L"Drawing Cards", LOGINFO);
		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Tick(deltaTime, game->playgameObjects.at(i));
		}
		game->playerOne->DrawACard();
		game->playerTwo->DrawACard();
		game->playerAI->DrawACard();
		break;
	}
	default:
		break;
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
	int moveX = 0;
	int moveAmount = 81;
	for (size_t i = 0; i < 20; i++)
	{
		int choice = rand() % 3;
		switch (choice)
		{
		case 0: { //red ring
			_char->cardPile->Deck.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/REDRINGCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(_char->handPos.x + moveX, _char->handPos.y, _char->handPos.z), glm::vec3(0, 0, 0), _char->defaultCardSize), "Red Ring Of Death Card", 50, 50, AttackCard::REDCIRCLE));
			break;
		}
		case 1: { //DDOS
			_char->cardPile->Deck.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/DDOSCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(_char->handPos.x + moveX, _char->handPos.y, _char->handPos.z), glm::vec3(0, 0, 0), _char->defaultCardSize), "DDOS Card", 70, 75, AttackCard::DDOS));
			break;
		}
		case 2: { //SQL
			_char->cardPile->Deck.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/SQLCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(_char->handPos.x + moveX, _char->handPos.y, _char->handPos.z), glm::vec3(0, 0, 0), _char->defaultCardSize), "SQL Card", 30, 10, AttackCard::SQL));
			break;
		}
		default: {
			i--;
			moveX -= moveAmount;
			Console_OutputLog(L"Deck Generation Choice out of bounds retrying...", LOGWARN);
			break;
		}
		}
		moveX += moveAmount;
	}
}

void populateGameObjectList() {
	Console_OutputLog(L"Creating Players...", LOGINFO);
	game->playerOne = new Human(new CardPile());
	game->playerTwo = new Human(new CardPile());
	game->playerAI = new AI(1, new CardPile());
	
	//Temporarly Deal Cards Here
	DealCardsRandom(game->playerOne);
	DealCardsRandom(game->playerTwo);
	DealCardsRandom(game->playerAI);

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

	//GAMEPLAY OBJECTS
	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/test.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerOne, true), new TickObject, Transform(glm::vec3(game->ScreenSize.x * -0.25f, game->ScreenSize.y * -0.25f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.2f, game->ScreenSize.y * 0.01f, 1.0f)), "Player One Health Bar"));
	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/test.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerOne, false), new TickObject, Transform(glm::vec3(game->ScreenSize.x * -0.25f, game->ScreenSize.y * -0.2f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.2f, game->ScreenSize.y * 0.01f, 1.0f)), "Player One Lines Bar"));
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


