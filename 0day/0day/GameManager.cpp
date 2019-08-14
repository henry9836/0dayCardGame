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
	Render();
	currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - pasttime) * 0.1f;
	pasttime = currentTime;

	//Tick Objects

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
	Console_OutputLog(L"Creating GameObjects...", LOGINFO);

	//GLOBALS

	game->gameObjects.push_back(new GameObject(SimpleTriangle(glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(-0.4f, 0.0f, 0.0f), glm::vec3(0.4f, 0.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Test Triangle", vector<GameObject::objectBehaviours>{GameObject::NONE}));
	game->gameObjects.push_back(new GameObject(new CTextLabel("Hello World", "/Resources/Fonts/TerminusTTF-4.47.0.ttf", glm::vec2(0,0), glm::vec3(0.4f, 0.0f, 0.0f), 1.0f, game, "Hello World Test"), "Hello World Text", vector<GameObject::objectBehaviours>{GameObject::NONE}));


	//MAINMENU OBJECTS

	game->maingameObjects.push_back(new GameObject(SimpleLine(glm::vec3(-0.8f, 0.9f, 0.0f), glm::vec3(-0.6f, 0.7f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "Test Line", vector<GameObject::objectBehaviours>{GameObject::DEMO}));

	//GAMEPLAY OBJECTS

	game->playgameObjects.push_back(new GameObject(SimpleFan(glm::vec3(0.7f, 0.5f, 0.0f), vector<glm::vec3>{glm::vec3(0.8f, 0.6f, 0.0f), glm::vec3(0.7f, 0.65f, 0.0f), glm::vec3(0.6f, 0.6f, 0.0f)}), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "Test Fan", vector<GameObject::objectBehaviours>{GameObject::NONE}));

}

void Start(int argc, char** argv)
{

	//Init OpenGL
	game = new Game;
	Console_OutputLog(L"Initialising OpenGL Components...", LOGINFO);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
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

	glClearColor(0.0, 0.0, 0.0, 1.0);

	//create GameObjects

	populateGameObjectList();

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
