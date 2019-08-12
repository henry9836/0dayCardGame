#include "GameManager.h"

Game* game;

bool DEBUG_MODE = true;

void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	for (size_t i = 0; i < game->gameObjects.size(); i++) //Render Objects
	{
		game->gameObjects.at(i)->Render();
	}

	glutSwapBuffers();
}

void Update() {
	Render();
}

void keyboard(unsigned char key, int, int) {
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
	wcout << "Mouse Clicked: " << button << endl;
}

void populateGameObjectList() {
	game->gameObjects.push_back(new GameObject(SimpleTriangle(glm::vec3(0.0f,0.8f,0.0f), glm::vec3(-0.4f,0.0f,0.0f), glm::vec3(0.4f,0.0f,0.0f)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Test Triangle"));
	game->gameObjects.push_back(new GameObject(SimpleLine(glm::vec3(-0.8f, 0.9f, 0.0f), glm::vec3(-0.6f, 0.7f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "Test Line"));
	game->gameObjects.push_back(new GameObject(SimpleFan(glm::vec3(0.8f, 0.9f, 0.0f), vector<glm::vec3>{glm::vec3(0.8f, 0.6f, 0.0f), glm::vec3(0.7f, 0.65f, 0.0f), glm::vec3(0.6f, 0.6f, 0.0f)}), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "Test Fan"));
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
