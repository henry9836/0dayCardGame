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

void Update() {

	if (game->currentScene == Scenes::SCENE_MAIN) {
		bool hasCard = false;
		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			/*if (game->playgameObjects.at(i)->type == GameObject::SIMPLEFAN) {
				hasCard = true;
			}*/
		}
		if (!hasCard) {
			//Console_OutputLog(L"Dealing Cards To Player", LOGINFO);
			//game->playgameObjects.push_back(new GameObject(SimpleFan(glm::vec3(0, 0, 0), vector<glm::vec3>{glm::vec3(-0.4f, 0.6f, 0.0f), glm::vec3(0.4f, 0.6f, 0.0f), glm::vec3(0.4f, -0.6f, 0.0f), glm::vec3(-0.4f, -0.6f, 0.0f), glm::vec3(-0.4f, 0.6f, 0.0f)}), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "Card", vector<GameObject::objectBehaviours>{GameObject::DEMOCARD}));
		}
	}


	Render();
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
}

void keyboard(unsigned char key, int, int) {

	//Main Menu
	if (game->currentScene == Scenes::SCENE_MAIN) {
		//Quit
		if (key == 27 || key == 113 || key == 81) { // ESC/Q 

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

			glutLeaveMainLoop();
		}

		
	}
	if (game->currentScene == Scenes::SCENE_GAME){
		if (key == 119 || key == 87) {
				bool hasCard = false;
				for (size_t i = 0; i < game->playgameObjects.size(); i++)
				{
					Console_OutputLog(L"Checking For Cards In Hand", LOGINFO);
					/*if (game->playgameObjects.at(i)->type == GameObject::SIMPLEFAN) {
						hasCard = true;
						Console_OutputLog(L"Player Delt 50 damage to enemy", LOGINFO);
						Console_OutputLog(L"Enemy health = 50/100", LOGINFO);
						Console_OutputLog(L"Taken Card Away From Player", LOGINFO);
						game->playgameObjects.at(i)->~GameObject();
						game->playgameObjects.erase(game->playgameObjects.begin() + i);
						i--;
					}*/
				}
				if (!hasCard) {
					Console_OutputLog(L"Player has no card remaing", LOGINFO);
				}
			}
	}
	if (key == 49) {
		Console_OutputLog(L"Switching to main menu", LOGINFO);
		game->currentScene = Scenes::SCENE_MAIN;
	}
	else if (key == 50) {
		Console_OutputLog(L"Switching to game", LOGINFO);
		game->currentScene = Scenes::SCENE_GAME;
	}
	wcout << "KEY: " << key << endl;
}

void keyboardSpecial(int key, int, int) {
	
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

void populateGameObjectList() {
	Console_OutputLog(L"Creating Players...", LOGINFO);
	game->playerOne = new Human();
	game->playerTwo = new Human();
	game->playerAI = new AI(1);
	
	Console_OutputLog(L"Creating GameObjects...", LOGINFO);

	//GLOBALS

	game->gameObjects.push_back(new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/test.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(-400, -200, 0), glm::vec3(0, 0, 0), glm::vec3(80.0f, 100.0f, 1.0f)), "Test Card 1"));
	game->gameObjects.push_back(new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/test.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(-300, -200, 0), glm::vec3(0, 0, 0), glm::vec3(80.0f, 100.0f, 1.0f)), "Test Card 2"));

	//MAINMENU OBJECTS
	
	game->maingameObjects.push_back(new GameObject(new RenderText(new CTextLabel("Main Menu\n 1. Main Menu\n 2. Play", "Resources/Fonts/TerminusTTF-4.47.0.ttf", glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, "Main Menu Text")),new IdleTick, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f)), "Main Menu Text"));

	//GAMEPLAY OBJECTS

}

void Start(int argc, char** argv)
{


	//Init OpenGL
	game = new Game;
	
	Console_OutputLog(L"Initialising OpenGL Components...", LOGINFO);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize((int)game->ScreenSize.x, (int)game->ScreenSize.y);

	glutCreateWindow("0day");

	if (glewInit() != GLEW_OK) {
		Console_OutputLog(L"Glew INIT FAILED! The program cannot recover from this error", LOGFATAL);
		system("pause");
		exit(0);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 0.0, 1.0);
	MeshManager::GetInstance();
	//create GameObjects
	game->camera.initializeCamera();
	game->camera.SwitchMode(Camera::ORTH, glm::vec3(0,0,0), glm::vec3(0,0,-2), glm::vec3(0,0,0), 2.0f, 0.0f);
	populateGameObjectList();
	//Start MeshManager


	//Start OpenGL

	Console_OutputLog(L"OpenGL Service Starting...", LOGINFO);

	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	// handlers for keyboard input
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);

	// mouse event handlers
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMovement);

	glutMainLoop();

}

Game::Game()
{
	Console_OutputLog(L"Constructing Game Class", LOGINFO);
	this->currentScene = Scenes::SCENE_MAIN;
}

Game::~Game()
{
	Console_OutputLog(L"Deconstructing Game Class", LOGINFO);
}

void Game::switchScene(Scenes newScene)
{
	this->currentScene = newScene;
}
