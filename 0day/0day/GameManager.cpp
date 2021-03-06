#include "GameManager.h"

Game* game;
AudioSystem* audio;

bool mouseDown = false;
float currentTime;
float deltaTime;
float pasttime;
bool goingup = true;
glm::vec3 backColor = glm::vec3(0.0, 0.0, 0.0);


void DealCardsRandom(Character* _char) {
	Console_OutputLog(L"Dealing Cards...", LOGINFO);

	int mSize = game->playerOne->cardPile->Deck.size();

	for (int i = 0; i < mSize; i++)
	{
		game->playerOne->cardPile->Deck.push_back(game->playerOne->cardPile->Deck.at(i));
	}

	mSize = game->playerTwo->cardPile->Deck.size();

	for (int i = 0; i < mSize; i++)
	{
		game->playerTwo->cardPile->Deck.push_back(game->playerTwo->cardPile->Deck.at(i));
	}
}


void Reset() {

	//Reset Game Values

	game->gameover = false;
	game->currentLvl = 1;
	game->currentScene = SCENE_MAIN;

	//empty vectors

	game->playerOne->cardPile->Deck.clear();
	game->playerOne->cardPile->Hand.clear();
	game->playerOne->cardPile->GY.clear();

	game->playerTwo->cardPile->Deck.clear();
	game->playerTwo->cardPile->Hand.clear();
	game->playerTwo->cardPile->GY.clear();

	game->playerAI->cardPile->Deck.clear();
	game->playerAI->cardPile->Hand.clear();
	game->playerAI->cardPile->GY.clear();

	//reset character values
	game->playerOne->Reset();
	game->playerTwo->Reset();
	game->playerAI->Reset();

	//stop music
	audio->Restart();


}

void DeckSelectionDestory()
{
	game->deckselectionObjects.clear();
	delete game->AddSelection;
	game->AddSelection = nullptr;
	delete game->Player1Selection;
	game->Player1Selection = nullptr;
	delete game->Player2Selection;
	game->Player2Selection = nullptr;
}

void DeckSelectionInit()
{
	//All player cards in the game get push in here.
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::fuzzer.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Fuzzer Card", 30, 30, AttackCard::FUZZER));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::robofight.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "RoboFight Card", 10, 5, AttackCard::ROBOFIGHT));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::ZERODAY.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "0day Card", 100, 0, AttackCard::ZERODAY));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::circle.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Red Ring Of Death Card", 50, 50, AttackCard::REDCIRCLE));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::dos.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "DDOS Card", 70, 75, AttackCard::DDOS));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::SQL.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "SQL Card", 20, 10, AttackCard::SQL));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::skull .data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Skull on screen Card", 5, 0, AttackCard::SKULL));
	game->deckselectionObjects.push_back(new AttackCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::stager.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Stager Card", 30, 15, AttackCard::STAGER));


	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::account.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Account Transfer Card", 20, 0, UtilityCard::ACCOUNT));
	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::systemreset.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "System Reset Card", 100, 0, UtilityCard::SYSTEMRESET));
	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::enhnaced.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Enhanced Card", 50, 0, UtilityCard::ENHNACED));
	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::enterkey.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Reinforced Enter Key Card", 20, 0, UtilityCard::REINFORCED));
	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::enumeration.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Enumertion Card", 25, 0, UtilityCard::ENUMERATION));
	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::FB.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "fork bomb Card", 40, 0, UtilityCard::FORKBOMB));
	game->deckselectionObjects.push_back(new UtilityCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::selfmod.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "self-modifiyng code Card", 5, 0, UtilityCard::SELFMODIFIYING));


	game->deckselectionObjects.push_back(new DefenceCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::tape.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Tape Over Webcam Card", 15, 0, DefenceCard::TAPE));
	game->deckselectionObjects.push_back(new DefenceCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::login.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Enhanced Login Protocal Card", 70, 0, DefenceCard::LOGIN));
	game->deckselectionObjects.push_back(new DefenceCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::firewall.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Firewall Card", 5, 0, DefenceCard::FIREWALL));
	game->deckselectionObjects.push_back(new DefenceCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::falseified.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "falsified credentials Card", 20, 0, DefenceCard::CREDS));
	game->deckselectionObjects.push_back(new DefenceCard(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::sunglasses.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObjectMoveable, Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Dark Sunglasses and trench coat Card", 40, 0, DefenceCard::SUNGLASSES));



	game->AddSelection = new Selection(game->deckselectionObjects, glm::vec3(game->ScreenSize.x * - 0.20f, game->ScreenSize.y * 0.35f, 0.0f), 5, 0.1f, 0.2f, game, 0, true, true);
	game->Player1Selection = new Selection(game->playerOne->cardPile->Deck, glm::vec3(game->ScreenSize.x * -0.45f, game->ScreenSize.y * 0.4f, 0.0f), 2, 0.09f, 0.17f, game, 1, false, false);
	game->Player2Selection = new Selection(game->playerTwo->cardPile->Deck, glm::vec3(game->ScreenSize.x * 0.35f, game->ScreenSize.y * 0.4f, 0.0f), 2, 0.09f, 0.17f, game, 2, false, false);
}

void FlashRed(glm::vec3* inColor, float deltaTime) {
	float increase = 0.005f * deltaTime;
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

void RenderEffects() {
	int offset = 0;
	int moveAmount = 51;

	//Player one
	//Generating lines
	if (game->playerOne->generateLine > 0) {
		game->p1EffectLines->transform.position = glm::vec3(game->p1EffectPos.x + (offset*moveAmount), game->p1EffectPos.y, game->p1EffectPos.z);
		game->p1EffectLines->Render();
		offset ++;
	}
	//stopped
	if (game->playerOne->lineStopped > 0) {
		game->p1EffectStopped->transform.position = glm::vec3(game->p1EffectPos.x + (offset * moveAmount), game->p1EffectPos.y, game->p1EffectPos.z);
		game->p1EffectStopped->Render();
		offset++;
	}

	offset = 0;

	//Player two
	//Generating lines
	if (game->playerTwo->generateLine > 0) {
		game->p2EffectLines->transform.position = glm::vec3(game->p2EffectPos.x + (offset * moveAmount), game->p2EffectPos.y, game->p2EffectPos.z);
		game->p2EffectLines->Render();
		offset++;
	}
	//stopped
	if (game->playerTwo->lineStopped > 0) {
		game->p2EffectStopped->transform.position = glm::vec3(game->p2EffectPos.x + (offset * moveAmount), game->p2EffectPos.y, game->p2EffectPos.z);
		game->p2EffectStopped->Render();
		offset++;
	}

	offset = 0;

	//AI
	//Generating lines
	if (game->playerAI->generateLine > 0) {
		game->aiEffectLines->transform.position = glm::vec3(game->aiEffectPos.x, game->aiEffectPos.y - (offset * moveAmount), game->aiEffectPos.z);
		game->aiEffectLines->Render();
		offset++;
	}
	//stopped
	if (game->playerAI->lineStopped > 0) {
		game->aiEffectStopped->transform.position = glm::vec3(game->aiEffectPos.x, game->aiEffectPos.y - (offset * moveAmount), game->aiEffectPos.z);
		game->aiEffectStopped->Render();
		offset++;
	}

	offset = 0;
}

void RenderCards() {
	int posOffset = 0;
	int moveAmount = 51;
	float scaleFactor = 3.0f;


	if (game->playerOne->currentHP > 0) {

		for (size_t i = 0; i < game->playerOne->cardPile->Hand.size(); i++)
		{
			//Reset any werid stuff
			game->playerOne->cardPile->Hand.at(i)->GetTransform() = Transform(glm::vec3(0,0,0), glm::vec3(0,0,0), game->playerOne->defaultCardSize);

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

		//Update target
		for (size_t i = 0; i < game->playerOne->cardPile->GY.size(); i++)
		{
			game->playerOne->cardPile->GY.at(i)->target = game->p1GYVisual->transform;
			game->playerOne->cardPile->GY.at(i)->target.position.z = game->p1GYVisual->transform.position.z + (0.01f * i);
			game->playerOne->cardPile->GY.at(i)->transform.position.z = game->p1GYVisual->transform.position.z + (0.01f * i);
		}

		//Render GY
		for (size_t i = 0; i < game->playerOne->cardPile->GY.size(); i++)
		{
			game->playerOne->cardPile->GY.at(i)->Render();
		}


	}

	posOffset = 0;

	if (game->playerTwo->currentHP > 0) {

		for (size_t i = 0; i < game->playerTwo->cardPile->Hand.size(); i++)
		{
			//Reset any werid stuff
			game->playerTwo->cardPile->Hand.at(i)->GetTransform() = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), game->playerTwo->defaultCardSize);

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

		

		//Update target
		for (size_t i = 0; i < game->playerTwo->cardPile->GY.size(); i++)
		{
			game->playerTwo->cardPile->GY.at(i)->target = game->p2GYVisual->transform;
			game->playerTwo->cardPile->GY.at(i)->target.position.z = game->p2GYVisual->transform.position.z + (0.01f * i);
			game->playerTwo->cardPile->GY.at(i)->transform.position.z = game->p2GYVisual->transform.position.z + (0.01f * i);
		}

		//Render GY
		for (size_t i = 0; i < game->playerTwo->cardPile->GY.size(); i++)
		{
			game->playerTwo->cardPile->GY.at(i)->Render();
		}


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
	switch (game->currentScene)
	{
	case Scenes::SCENE_MAIN:
	{
		game->background->Render();
		game->StartMenu->Render();
		for (size_t i = 0; i < game->maingameObjects.size(); i++)
		{
			game->maingameObjects.at(i)->Render();
		}
		break;
	}
	case Scenes::SCENE_SELECTION:
	{
		game->background->Render();
		game->AddSelection->Render();
		game->Player1Selection->Render();
		game->Player2Selection->Render();
		break;
	}
	case Scenes::SCENE_GAME:
	{

		if (!(game->playerOne->currentHP <= 0) && !(game->playerTwo->currentHP <= 0))
			game->gameBackground->Render();

		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Render();
		}

		game->playerAI->gameObject->Render();

		if (game->playerOne->cardPile->Deck.size() > 0) {
			game->p1DeckVisual->Render();
		}
		if (game->playerOne->cardPile->GY.size() > 0) {
			game->p1GYVisual->Render();
		}
		
		if (game->playerTwo->cardPile->Deck.size() > 0) {
			game->p2DeckVisual->Render();
		}
		if (game->playerTwo->cardPile->GY.size() > 0) {
			game->p2GYVisual->Render();
		}

		RenderEffects();
		RenderCards();
		

		game->levelText->Render();

		break;
	}
	case Scenes::SCENE_HOWTOPLAY:
	{
		if (game->isSecondPage == false)
		{
			game->background->Render();
			for (size_t i = 0; i < game->howtoplayObjects.size(); i++)
			{
				game->howtoplayObjects.at(i)->Render();
			}
		}
		else
		{
			game->Page2->Render();
		}
		game->HowToPlayMenu->Render();

		break;
	}
	case Scenes::SCENE_LOSE: {
		game->background->Render();
		for (size_t i = 0; i < game->lostObjects.size(); i++)
		{
			game->lostObjects.at(i)->Render();
		}
		game->levelText->Render();
		break;
	}
	default:
		break;
	}


	glutSwapBuffers();
}

void PlayCard(Character* _caster, Character* _target, Character* _otherPlayer) {
	//Sanity Check
	if ((_caster->cardPile->Hand.size() >= 1) && (_caster->selectedCardVector <  (int)_caster->cardPile->Hand.size()) && (_caster->selectedCardVector >= 0)) {

		//Check cost

		if (_caster->currentLines >= _caster->cardPile->Hand.at(_caster->selectedCardVector)->cost) {

			//SFX
			audio->Play(AudioSystem::SUCCESS);

			//Charge player

			_caster->currentLines -= _caster->cardPile->Hand.at(_caster->selectedCardVector)->cost;

			//play effect

			_caster->cardPile->Hand.at(_caster->selectedCardVector)->Action(_caster, _target, _otherPlayer);

			//move card
			if (true) {
				if ((_caster->cardPile->Hand.size() > 0) && ((static_cast<int>(_caster->cardPile->Hand.size()) -1) >= _caster->selectedCardVector)) {
					_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(_caster->selectedCardVector));
				}
			}

			//remove card

			if ((_caster->cardPile->Hand.size() > 0) &&  ((static_cast<int>(_caster->cardPile->Hand.size()) - 1) >= _caster->selectedCardVector)) {
				_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + _caster->selectedCardVector);
			}
			//am I beyond range?

			if (_caster->selectedCardVector > static_cast<int>(_caster->cardPile->Hand.size() - 1)) {
				_caster->selectedCardVector = _caster->cardPile->Hand.size() - 1;
			}
			else if (_caster->selectedCardVector < 0) {
				_caster->selectedCardVector = 0;
			}

		}
		//Player cannot afford card
		else {
			audio->Play(AudioSystem::DENY);
		}
	}
	//Sanity Check Failed
	else {
		//Reset selected card to 0 something went wrong
		Console_OutputLog(L"BUG ID: 1 Behaviour Caught, applying fix", LOGWARN);
		_caster->selectedCardVector = 0;
	}
}

void PlayerInputLoop() {

	//Player1 
	if (game->playerOne->currentHP > 0) {

		if ((CInputManager::KeyArray[119] == KEY_FIRST_PRESS) || (CInputManager::KeyArray[87] == KEY_FIRST_PRESS)) { //W Play Card

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

			if (game->playerOne->selectedCardVector < static_cast<int>(game->playerOne->cardPile->Hand.size() - 1)) {
				game->playerOne->selectedCardVector++;
			}
		}
	}

	//Player2

	if (game->playerTwo->currentHP > 0) {

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

			if (game->playerTwo->selectedCardVector < static_cast<int>(game->playerTwo->cardPile->Hand.size() - 1)) {
				game->playerTwo->selectedCardVector++;
			}
		}
	}

}


void TickCards(float _d) {
	for (size_t i = 0; i < game->playerOne->cardPile->Deck.size(); i++)
	{
		game->playerOne->cardPile->Deck.at(i)->Tick(_d, game->playerOne->cardPile->Deck.at(i));
	}
	for (size_t i = 0; i < game->playerOne->cardPile->Hand.size(); i++)
	{
		game->playerOne->cardPile->Hand.at(i)->Tick(_d, game->playerOne->cardPile->Hand.at(i));
	}
	for (size_t i = 0; i < game->playerOne->cardPile->GY.size(); i++)
	{
		game->playerOne->cardPile->GY.at(i)->Tick(_d, game->playerOne->cardPile->GY.at(i));
	}

	for (size_t i = 0; i < game->playerTwo->cardPile->Deck.size(); i++)
	{
		game->playerTwo->cardPile->Deck.at(i)->Tick(_d, game->playerTwo->cardPile->Deck.at(i));
	}
	for (size_t i = 0; i < game->playerTwo->cardPile->Hand.size(); i++)
	{
		game->playerTwo->cardPile->Hand.at(i)->Tick(_d, game->playerTwo->cardPile->Hand.at(i));
	}
	for (size_t i = 0; i < game->playerTwo->cardPile->GY.size(); i++)
	{
		game->playerTwo->cardPile->GY.at(i)->Tick(_d, game->playerTwo->cardPile->GY.at(i));
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

	switch (game->currentScene)
	{
	case Scenes::SCENE_MAIN:
	{
		if (!game->once) {
			audio->Restart();
			audio->Play(AudioSystem::BACK);
			game->once = true;
			game->Selectonce = false;
			game->Gameonce = false;
		}
		int tempOutput = NULL;
		game->StartMenu->Process(tempOutput);
		CInputManager::ProcessKeyInput();
		switch (tempOutput)
		{
		case 0:
			game->currentScene = Scenes::SCENE_SELECTION;
			DeckSelectionInit();
			break;
		case 1: // Would be option screen
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
		break;
	}
	case Scenes::SCENE_SELECTION:
	{
		/*if (!game->Selectonce) {
			audio->Restart();
			audio->Play(AudioSystem::SELECTBACK);
			game->Gameonce = false;
			game->once = false;
			game->Selectonce = true;
		}*/
		game->AddSelection->Process(game->playerOne, game->playerTwo, audio);
		game->Player1Selection->Process(game->playerOne, game->playerTwo, audio);
		game->Player2Selection->Process(game->playerOne, game->playerTwo, audio);
		if ((CInputManager::KeyArray['\r'] == KEY_FIRST_PRESS || CInputManager::KeyArray['f'] == KEY_FIRST_PRESS) && (game->playerOne->cardPile->Deck.size() >= 10 && game->playerTwo->cardPile->Deck.size() >= 10))
		{
			game->currentScene = Scenes::SCENE_GAME;
			DealCardsRandom(game->playerOne);
			DealCardsRandom(game->playerTwo);
			DealCardsRandom(game->playerAI);
			DeckSelectionDestory();
		}
		CInputManager::ProcessKeyInput();
		break;
	}
	case Scenes::SCENE_GAME:
	{
		//Sanity Checks
		if (game->playerOne->currentHP > game->playerOne->maxHP) {
			game->playerOne->currentHP = game->playerOne->maxHP;
		}
		if (game->playerTwo->currentHP > game->playerTwo->maxHP) {
			game->playerTwo->currentHP = game->playerTwo->maxHP;
		}
		if (game->playerAI->currentHP > game->playerAI->maxHP) {
			game->playerAI->currentHP = game->playerAI->maxHP;
		}
	

		for (size_t i = 0; i < game->playgameObjects.size(); i++)
		{
			game->playgameObjects.at(i)->Tick(deltaTime, game->playgameObjects.at(i));
		}
		
		if (!game->Gameonce) {
			audio->Restart();
			audio->Play(AudioSystem::GAMEBACK);
			game->Gameonce = true;
			game->once = false;
			game->Selectonce = false;
		}

		TickCards(deltaTime);

		game->playerOne->Tick(deltaTime, game->currentLvl);
		game->playerTwo->Tick(deltaTime, game->currentLvl);
		game->playerAI->Tick(deltaTime , game->currentLvl);

		PlayerInputLoop();
		CInputManager::ProcessKeyInput();

		//Check Game Conditions

		//AI Has Died

		if ((game->playerOne->currentHP <= 0) && (game->playerTwo->currentHP <= 0)) 
		{
			game->gameover = true;
		}

		//resets level
		if (game->playerAI->currentHP <= 0) 
		{
			game->gameover = false;
			game->currentLvl++;
			game->playerAI->updateLevel(game->currentLvl);
			Console_OutputLog(to_wstring("AI has been defeated, you have now progress to level: " + to_string(game->currentLvl)), LOGINFO);

			game->levelText->SetText("Level: " + to_string(game->currentLvl));

			game->playerOne->damageMult = 1.0f;
			game->playerTwo->damageMult = 1.0f;

			game->playerAI->LinesMult = game->playerAI->LinesMultInit;
			game->playerOne->damageMult = 1.0f;
			game->playerTwo->damageMult = 1.0f;

			game->playerOne->maxHP = 100.0f;
			game->playerTwo->maxHP = 100.0f;

			game->playerOne->currentHP = game->playerOne->maxHP;
			game->playerTwo->currentHP = game->playerTwo->maxHP;
			game->playerAI->currentHP = game->playerAI->maxHP;

			game->playerOne->currentLines = 0.0f;
			game->playerTwo->currentLines = 0.0f;
			game->playerAI->currentLines = 0.0f;

			
			for (int i = 0; i < (signed int)game->playerOne->cardPile->Hand.size(); i++)
			{
				game->playerOne->cardPile->GY.push_back(game->playerOne->cardPile->Hand.at(0));
				game->playerOne->cardPile->Hand.erase(game->playerOne->cardPile->Hand.begin());
				i--;
			}
			for (int i = 0; i < (signed int)game->playerTwo->cardPile->Hand.size(); i++)
			{
				game->playerTwo->cardPile->GY.push_back(game->playerTwo->cardPile->Hand.at(0));
				game->playerTwo->cardPile->Hand.erase(game->playerTwo->cardPile->Hand.begin());
				i--;
			}

			game->playerOne->moveGYToDeck();
			game->playerTwo->moveGYToDeck();


		}

		if (game->gameover) {
			//reset and kick back to lose screen
			Console_OutputLog(L"GAMEOVER", LOGINFO);
			Reset();
			game->currentScene = SCENE_LOSE;
		}

		break;
		
		
	}
	case Scenes::SCENE_HOWTOPLAY:
	{
		int tempOutput = NULL;
		game->HowToPlayMenu->Process(tempOutput);
		for (size_t i = 0; i < game->howtoplayObjects.size(); i++)
		{
			game->howtoplayObjects.at(i)->Tick(deltaTime, game->howtoplayObjects.at(i));
		}
		CInputManager::ProcessKeyInput();
		switch (tempOutput)
		{
		case 0:
			game->isSecondPage = !game->isSecondPage;
			break;
		case 1:
			game->currentScene = Scenes::SCENE_MAIN;
			break;
		default:
			break;
		}

	}
	case Scenes::SCENE_LOSE: {
		if (CInputManager::KeyArray['\r'] == KEY_FIRST_PRESS || CInputManager::KeyArray[' '] == KEY_FIRST_PRESS) {
			game->currentScene = Scenes::SCENE_MAIN;
		}
		CInputManager::ProcessKeyInput();
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

void populateGameObjectList() {
	Console_OutputLog(L"Creating Players...", LOGINFO);
	game->playerOne = new Human(new CardPile(glm::vec3(-700.0f, -350.0f, 0.5f)), 100.0f, new GameObject(new RenderObject(), new IdleTick(), Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Player One"), false);
	game->playerTwo = new Human(new CardPile(glm::vec3(100.0f, -350.0f, 0.5f)), 100.0f, new GameObject(new RenderObject(), new IdleTick(), Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0,0,0)), "Player Two"), false);
	game->playerAI = new AI(game->currentLvl, new CardPile(glm::vec3(-1200.0f, 350.0f, 0.5f)), 100.0f, new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/tmpAI.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(0, 250, 0.5f), glm::vec3(0, 0, 0), glm::vec3(100.0f, 100.0f, 1.0f)), "AI"), true, game->playerOne, game->playerTwo);
	
	//Temporarly Deal Cards Here


	Console_OutputLog(L"Creating GameObjects...", LOGINFO);

	//GLOBALS

	//MAINMENU OBJECTS

#pragma region StartMenu

	std::vector<std::string> StartOpt;
	StartOpt.push_back("Start");
	StartOpt.push_back("How To Play");
	StartOpt.push_back("Quit");
	game->maingameObjects.push_back(new GameObject(new RenderText(new CTextLabel("0Day", Utility::NormalFontString.data(), glm::vec2(0.0f, (game->ScreenSize.y / 2) - 150), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f, game, ("test1"))), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "vText"));

	game->StartMenu = new CMenu(StartOpt, glm::vec2(0.0f, 0.0f), game);

#pragma endregion

	//HOW TO PLAY OBJECTS
#pragma region how to play menu 

	std::vector<std::string> menuopts;

	menuopts.push_back("Next Page");
	menuopts.push_back("Back");

	game->HowToPlayMenu = new CMenu(menuopts, glm::vec2((game->ScreenSize.x /2) - 200, (-game->ScreenSize.y / 2) + 50), game);

	game->howtoplayObjects.push_back(new GameObject(new RenderText(new CTextLabel("Player 1: A/D to change selection, W to play a card, ", Utility::NormalFontString.data(), glm::vec2((-game->ScreenSize.x / 2) + 50, (game->ScreenSize.y / 2) - 50), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, ("test1"))), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "vText"));
	game->howtoplayObjects.push_back(new GameObject(new RenderText(new CTextLabel("Player 2: </> to change selection, Up Arrow to play a card", Utility::NormalFontString.data(), glm::vec2((-game->ScreenSize.x / 2) + 50, (game->ScreenSize.y / 2) - 100), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, ("test1"))), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "vText"));
	game->howtoplayObjects.push_back(new GameObject(new RenderText(new CTextLabel("Card Colour types are Red = Attack, \nBlue = Defence, Purple = Utility", Utility::NormalFontString.data(), glm::vec2((-game->ScreenSize.x / 2) + 50, (-game->ScreenSize.y / 2) + 100), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, ("Type of Cards Text"))), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)), "vText"));
	game->howtoplayObjects.push_back(new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::stager.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * -0.25f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.125f, game->ScreenSize.y * 0.25, 1.0f)), "test image"));
	game->Page2 = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::Page2.data()), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.5f, game->ScreenSize.y * 0.5, 1.0f)), "test image");

	game->lostObjects.push_back(new GameObject(new RenderText(new CTextLabel("Game Over\nYou have lost the battle against the robots\nPress Space To Continue...", Utility::NormalFontString.data(), glm::vec2(game->ScreenSize.x * -0.25f, game->ScreenSize.y * 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, ("Lose Text"))), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * -0.35f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), "Lose Text"));

	game->levelText = new CTextLabel("Level: 1", Utility::NormalFontString.data(), glm::vec2(game->ScreenSize.x * -0.45f, game->ScreenSize.y * 0.45f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, game, ("Level Text"));
#pragma endregion


	//GAMEPLAY OBJECTS
	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/barLines.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerOne, true), new TickObject, Transform(glm::vec3(game->ScreenSize.x * -0.35f, game->ScreenSize.y * -0.21f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.09f, game->ScreenSize.y * 0.008f, 1.0f)), "Player One Health Bar"));
	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/barHealth.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerOne, false), new TickObject, Transform(glm::vec3(game->ScreenSize.x * -0.15f, game->ScreenSize.y * -0.21f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.09f, game->ScreenSize.y * 0.008f, 1.0f)), "Player One Lines Bar"));

	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/barLines.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerTwo, true), new TickObject, Transform(glm::vec3(game->ScreenSize.x * 0.15f, game->ScreenSize.y * -0.21f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.09f, game->ScreenSize.y * 0.008f, 1.0f)), "Player Two Health Bar"));
	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/barHealth.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerTwo, false), new TickObject, Transform(glm::vec3(game->ScreenSize.x * 0.35f, game->ScreenSize.y * -0.21f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.09f, game->ScreenSize.y * 0.008f, 1.0f)), "Player Two Lines Bar"));

	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/barLines.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerAI, true), new TickObject, Transform(glm::vec3(game->ScreenSize.x * 0.00005f, game->ScreenSize.y * 0.40f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.09f, game->ScreenSize.y * 0.008f, 1.0f)), "Player AI Health Bar"));
	game->playgameObjects.push_back(new GameObject(new BarsRender(MeshManager::GetMesh(Object_Attributes::BAR_ENTITY), MeshManager::SetTexture("Resources/Textures/barHealth.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER), game->playerAI, false), new TickObject, Transform(glm::vec3(game->ScreenSize.x * 0.00005f, game->ScreenSize.y * 0.45f, 0), glm::vec3(0, 0, 0), glm::vec3(game->ScreenSize.x * 0.09f, game->ScreenSize.y * 0.008f, 1.0f)), "Player AI Lines Bar"));

	game->p1DeckVisual = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/CardBack.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * -0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), game->playerOne->defaultCardSize), "Deck Visual");
	game->p1GYVisual = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/CardBack.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.0f, game->ScreenSize.y * -0.25f, 0), glm::vec3(0, 0, 90), game->playerOne->defaultCardSize), "Deck Visual");

	game->p2DeckVisual = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/CardBack.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), game->playerOne->defaultCardSize), "Deck Visual");
	game->p2GYVisual = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/CardBack.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.0f, game->ScreenSize.y * -0.35f, 0), glm::vec3(0, 0, 90), game->playerOne->defaultCardSize), "Deck Visual");

	game->gameBackground = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/ground.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, -0.9f), glm::vec3(0, 0, 0), glm::vec3(1000, 1000, 1)), "Background Layer");
	game->background = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/background.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(0.0f, 0.0f, -0.9f), glm::vec3(0, 0, 0), glm::vec3(1000, 1000, 1)), "Background");

	//Effect Visuals

	glm::vec3 effectScale = glm::vec3(20, 20, 1);

	game->p1EffectLines = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/keyboard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), effectScale), "Lines Effect Visual");
	game->p1EffectStopped = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/lock.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), effectScale), "Stopped Effect Visual");
	
	game->p2EffectLines = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/keyboard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), effectScale), "Lines Effect Visual");
	game->p2EffectStopped = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/lock.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), effectScale), "Stopped Effect Visual");
	
	game->aiEffectLines = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/keyboard.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), effectScale), "Lines Effect Visual");
	game->aiEffectStopped = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture("Resources/Textures/lock.png"), game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new IdleTick, Transform(glm::vec3(game->ScreenSize.x * 0.45f, game->ScreenSize.y * -0.15f, 0), glm::vec3(0, 0, 0), effectScale), "Stopped Effect Visual");

	game->p1EffectPos = glm::vec3(game->ScreenSize.x * -0.4f, game->ScreenSize.y * -0.13f, 0);
	game->p2EffectPos = glm::vec3(game->ScreenSize.x * 0.1f, game->ScreenSize.y * -0.13f, 0);
	game->aiEffectPos = glm::vec3(game->ScreenSize.x * 0.13f, game->ScreenSize.y * 0.4f, 0);

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

	//audio

	audio = new AudioSystem();
	audio->AudioInit();


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


