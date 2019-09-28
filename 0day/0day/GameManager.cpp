#include "GameManager.h"

Game* game;

bool mouseDown = false;
float currentTime;
float deltaTime;
float pasttime;
bool goingup = true;
glm::vec3 backColor = glm::vec3(0.0, 0.0, 0.0);

void FlashRed(glm::vec3* inColor, float deltaTime) {
	float increase = 0.01f * deltaTime;
	if (goingup) {
		if (inColor->x >= 1) {
			goingup = !goingup;
		}
		else {
			inColor->x += increase;
		}
	}
	else {
		if (inColor->x <= 0) {
			goingup = !goingup;
		}
		else {
			inColor->x -= increase;
		}
	}
}

void RenderCards() {
	int posOffset = 0;
	int moveAmount = 51;
	float scaleFactor = 3.0f;

	for (size_t i = 0; i < game->playerOne->cardPile->Hand.size(); i++)
	{
		//Create Positions for cards dyanmically
		game->playerOne->cardPile->Hand.at(i)->GetTransform().position = glm::vec3(game->playerOne->cardPile->handPos.x + (posOffset * moveAmount), game->playerOne->cardPile->handPos.y, game->playerOne->cardPile->handPos.z);

		if (i == game->playerOne->selectedCardVector) { //make card bigger
			game->playerOne->cardPile->Hand.at(i)->GetTransform().position = glm::vec3(game->playerOne->cardPile->Hand.at(i)->GetTransform().position.x, game->playerOne->cardPile->Hand.at(i)->GetTransform().position.y, game->playerOne->cardPile->handPos.z + 0.1f);
			game->playerOne->cardPile->Hand.at(i)->GetTransform().scale = game->playerOne->defaultCardSize * scaleFactor;
		}
		else {
			game->playerOne->cardPile->Hand.at(i)->GetTransform().position = glm::vec3(game->playerOne->cardPile->Hand.at(i)->GetTransform().position.x, game->playerOne->cardPile->Hand.at(i)->GetTransform().position.y, game->playerOne->cardPile->handPos.z);
			game->playerOne->cardPile->Hand.at(i)->GetTransform().scale = game->playerOne->defaultCardSize;
		}
		game->playerOne->cardPile->Hand.at(i)->Render();

		posOffset++;
	}

	posOffset = 0;

	for (size_t i = 0; i < game->playerTwo->cardPile->Hand.size(); i++)
	{
		//Create Positions for cards dyanmically
		game->playerTwo->cardPile->Hand.at(i)->GetTransform().position = glm::vec3(game->playerTwo->cardPile->handPos.x + (posOffset * moveAmount), game->playerTwo->cardPile->handPos.y, game->playerTwo->cardPile->handPos.z);

		if (i == game->playerTwo->selectedCardVector) { //make card bigger
			game->playerTwo->cardPile->Hand.at(i)->GetTransform().position = glm::vec3(game->playerTwo->cardPile->Hand.at(i)->GetTransform().position.x, game->playerTwo->cardPile->Hand.at(i)->GetTransform().position.y, game->playerTwo->cardPile->handPos.z + 0.1f);
			game->playerTwo->cardPile->Hand.at(i)->GetTransform().scale = game->playerTwo->defaultCardSize * scaleFactor;
		}
		else {
			game->playerTwo->cardPile->Hand.at(i)->GetTransform().position = glm::vec3(game->playerTwo->cardPile->Hand.at(i)->GetTransform().position.x, game->playerTwo->cardPile->Hand.at(i)->GetTransform().position.y, game->playerTwo->cardPile->handPos.z);
			game->playerTwo->cardPile->Hand.at(i)->GetTransform().scale = game->playerTwo->defaultCardSize;
		}
		game->playerTwo->cardPile->Hand.at(i)->Render();

		posOffset++;
	}

	//DEBUG AI
	for (size_t i = 0; i < game->playerAI->cardPile->Hand.size(); i++)
	{
		game->playerAI->cardPile->Hand.at(i)->Render();
	}
}

void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glClearColor(backColor.x, backColor.y, backColor.z, 1.0);

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

		RenderCards();

	}
	else if (game->currentScene == Scenes::SCENE_HOWTOPLAY)
	{
		game->HowToPlayMenu->Render();
		for (size_t i = 0; i < game->howtoplayObjects.size(); i++)
		{
			game->howtoplayObjects.at(i)->Render();
		}

	}




	glutSwapBuffers();
}

void PlayCard(Character* _caster, Character* _target, Character* _otherPlayer) {
	if (_caster->cardPile->Hand.size() >= 1) {

		//Check cost

		if (_caster->currentLines >= _caster->cardPile->Hand.at(_caster->selectedCardVector)->cost) {

			//Charge player

			_caster->currentLines -= _caster->cardPile->Hand.at(_caster->selectedCardVector)->cost;

			//play effect

			_caster->cardPile->Hand.at(_caster->selectedCardVector)->Action(_caster, _target, _otherPlayer);

			//move card
			if (true) {
				_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(_caster->selectedCardVector));
			}

			//remove card

			_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + _caster->selectedCardVector);

			//am I beyond range?

			if (_caster->selectedCardVector > _caster->cardPile->Hand.size() - 1) {
				_caster->selectedCardVector = _caster->cardPile->Hand.size() - 1;
			}
			else if (_caster->selectedCardVector < 0) {
				_caster->selectedCardVector = 0;
			}

		}
	}
}

void PlayerInputLoop() {

	//Player1 
	if ((CInputManager::KeyArray[119] == KEY_FIRST_PRESS) || (CInputManager::KeyArray[87] == KEY_FIRST_PRESS)) { //W Play Card

		//Sanity Check

		PlayCard(game->playerOne, game->playerAI, game->playerTwo);

		
	}
	if ((CInputManager::KeyArray[83] == KEY_FIRST_PRESS) || (CInputManager::KeyArray[115] == KEY_FIRST_PRESS)) { //S

	}
	if ((CInputManager::KeyArray[65] == KEY_FIRST_PRESS) || (CInputManager::KeyArray[97] == KEY_FIRST_PRESS)) { //A

		if (game->playerOne->selectedCardVector > 0) {
			game->playerOne->selectedCardVector--;
		}
	}
	if ((CInputManager::KeyArray[68] == KEY_FIRST_PRESS) || (CInputManager::KeyArray[100] == KEY_FIRST_PRESS)) { //D

		if (game->playerOne->selectedCardVector < game->playerOne->cardPile->Hand.size() - 1) {
			game->playerOne->selectedCardVector++;
		}
	}

	//Player2
	if (CInputManager::KeySpecialArray[GLUT_KEY_DOWN] == KEY_FIRST_PRESS) { //DOWN
		//cycle
	}
	if (CInputManager::KeySpecialArray[GLUT_KEY_UP] == KEY_FIRST_PRESS) { //UP
		PlayCard(game->playerTwo, game->playerAI, game->playerOne);
	}
	if (CInputManager::KeySpecialArray[GLUT_KEY_LEFT] == KEY_FIRST_PRESS) { //LEFT

		if (game->playerTwo->selectedCardVector > 0) {
			game->playerTwo->selectedCardVector--;
		}
	}
	if (CInputManager::KeySpecialArray[GLUT_KEY_RIGHT] == KEY_FIRST_PRESS) { //RIGHT

		if (game->playerTwo->selectedCardVector < game->playerTwo->cardPile->Hand.size()-1){
			game->playerTwo->selectedCardVector++;
		}
	}



}

//Update Loop
void Update() {

	currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - pasttime) * 0.1f;
	pasttime = currentTime;

	FlashRed(&backColor, deltaTime);

	//Tick Objects

	game->camera.Tick(game->ScreenSize, deltaTime);

	for (size_t i = 0; i < game->gameObjects.size(); i++)
	{
		game->gameObjects.at(i)->Tick(deltaTime, game->gameObjects.at(i));
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
			game->currentScene = Scenes::SCENE_HOWTOPLAY;
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
	}
	else if (game->currentScene == Scenes::SCENE_GAME) {
		//Draw Cards needs to be improved a lot
		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Tick(deltaTime, game->playgameObjects.at(i));
		}

		game->playerOne->Tick(deltaTime);
		game->playerTwo->Tick(deltaTime);
		game->playerAI->Tick(deltaTime);

		PlayerInputLoop();
		CInputManager::ProcessKeyInput();
		
		
	}
	else if (game->currentScene == Scenes::SCENE_HOWTOPLAY)
	{
		int tempOutput = NULL;
		game->HowToPlayMenu->Process(tempOutput);
		CInputManager::ProcessKeyInput();
		switch (tempOutput)
		{
		case 0:
			game->currentScene = Scenes::SCENE_MAIN;
			break;
		default:
			break;
		}

		for (size_t i = 0; i < game->howtoplayObjects.size(); i++)
		{
			game->howtoplayObjects.at(i)->Tick(deltaTime, game->howtoplayObjects.at(i));
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
	int moveX = 0;
	int moveAmount = 51;
	int dealAmount = 20;
	for (size_t i = 0; i < dealAmount; i++)
	{
		int choice = rand() % 3;
		switch (choice)
		{
		case 0: { //red ring
			_char->cardPile->Deck.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/REDRINGCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(_char->cardPile->handPos.x + moveX, _char->cardPile->handPos.y, _char->cardPile->handPos.z), glm::vec3(0, 0, 0), _char->defaultCardSize), "Red Ring Of Death Card", 50, 50, AttackCard::REDCIRCLE));
			break;
		}
		case 1: { //DDOS
			_char->cardPile->Deck.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/DDOSCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(_char->cardPile->handPos.x + moveX, _char->cardPile->handPos.y, _char->cardPile->handPos.z), glm::vec3(0, 0, 0), _char->defaultCardSize), "DDOS Card", 70, 75, AttackCard::DDOS));
			break;
		}
		case 2: { //SQL
			_char->cardPile->Deck.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/SQLCard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject, Transform(glm::vec3(_char->cardPile->handPos.x + moveX, _char->cardPile->handPos.y, _char->cardPile->handPos.z), glm::vec3(0, 0, 0), _char->defaultCardSize), "SQL Card", 30, 10, AttackCard::SQL));
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
	game->playerOne = new Human(new CardPile(glm::vec3(-700.0f, -350.0f, 0.5f)));
	game->playerTwo = new Human(new CardPile(glm::vec3(100.0f, -350.0f, 0.5f)));
	game->playerAI = new AI(1, new CardPile(glm::vec3(-1200.0f, 350.0f, 0.5f)));
	
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
	StartOpt.push_back("How To Play");
	StartOpt.push_back("Quit");
	game->StartMenu = new CMenu(StartOpt, glm::vec2(0.0f, 0.0f), game);
#pragma endregion

	//HOW TO PLAY objects
#pragma region how to play menu 

	std::vector<std::string> menuopts;
	menuopts.push_back("back");

	game->HowToPlayMenu = new CMenu(menuopts, glm::vec2(0.0f, 0.0f), game);

	game->howtoplayObjects.push_back(new GameObject(new RenderText(new CTextLabel("insert instructions how to play here", Utility::NormalFontString.data(), glm::vec2(50.0f, 50.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, ("test1"))), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "vText"));


#pragma endregion


	//GAMEPLAY OBJECTS

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

	for (size_t i = 0; i < game->howtoplayObjects.size(); i++)
	{
		game->howtoplayObjects.at(i)->~GameObject();
		game->howtoplayObjects.erase(game->howtoplayObjects.begin() + i);
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

	glClearColor(backColor.x, backColor.y, backColor.z, 1.0);
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

