#include "Selection.h"

Selection::Selection(std::vector<Card*> _OptVect, glm::vec3 _Pos, int _Length, float _SeperationDistanceX, float _SeperationDistanceY, Game * _Game, int _Menu, bool _playerOneIsOn, bool _playerTwoIsOn)
{
	NumMenuOptions = 0;
	StartPosition = _Pos;
	glm::vec3 NewPosition = _Pos;
	OptionVect = _OptVect;
	NumMenuOptions = _OptVect.size() - 1;
	MenuType = _Menu;
	p_Game = _Game;
	Length = _Length;
	SeperationDistanceX = _SeperationDistanceX;
	SeperationDistanceY = _SeperationDistanceY;
	playerOneIsOn = _playerOneIsOn;
	playerTwoIsOn = _playerTwoIsOn;
	indicatorPlayer1 = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::Player1Indicator.data()), _Game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject(), Transform(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(p_Game->ScreenSize.x * 0.015f,p_Game->ScreenSize.y * 0.015f,0)), "Player 1 Indicator");
	indicatorPlayer2 = new GameObject(new RenderObject(MeshManager::GetMesh(Object_Attributes::CARD_ENTITY), MeshManager::SetTexture(Textures::Player2Indicator.data()), _Game, MeshManager::GetShaderProgram(Shader_Attributes::BASIC_SHADER)), new TickObject(), Transform(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(p_Game->ScreenSize.x * 0.015f, p_Game->ScreenSize.y * 0.015f, 0)), "Player 2 Indicator");
	if (_Menu == 0)
	{
		//Start Text
		Start = new CTextLabel("Hit 'f' or 'Enter' to Start\n10 Cards are Required to Start", Utility::NormalFontString.data(), glm::vec2(p_Game->ScreenSize.x * - 0.2f, p_Game->ScreenSize.y * -0.4f), glm::vec3(), 1.0f, _Game, "Start Text");
	}
	int iterator = 0;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (int i = 0; i < _Length; i++)
		{
			if (iterator > NumMenuOptions)
			{
				break;
			}
			OptionVect[iterator]->GetTransform().position = NewPosition;
			NewPosition.x += _Game->ScreenSize.x * _SeperationDistanceX;
			iterator++;
		}
		NewPosition.x = StartPosition.x;
		NewPosition.y -= _Game->ScreenSize.y * _SeperationDistanceY;
	}
}

Selection::~Selection()
{
	OptionVect.clear();
}

void Selection::IncrementMenu(int _Player)
{
	if (OptionVect.size() != 0)
	{
		if (_Player == 1)
		{
			if (CurrentOptionPlayerOne == NumMenuOptions) CurrentOptionPlayerOne = 0;
			else ++CurrentOptionPlayerOne;
		}
		else if (_Player == 2)
		{
			if (CurrentOptionPlayerTwo == NumMenuOptions) CurrentOptionPlayerTwo = 0;
			else ++CurrentOptionPlayerTwo;
		}
	}
}

void Selection::DecrementMenu(int _Player)
{
	if (OptionVect.size() != 0)
	{
		if (_Player == 1)
		{
			if (CurrentOptionPlayerOne == 0) CurrentOptionPlayerOne = NumMenuOptions;
			else --CurrentOptionPlayerOne;
		}
		else if (_Player == 2)
		{
			if (CurrentOptionPlayerTwo == 0) CurrentOptionPlayerTwo = NumMenuOptions;
			else --CurrentOptionPlayerTwo;
		}
	}
}

void Selection::ResetRender()
{
	glm::vec3 NewPosition = StartPosition;
	int iterator = 0;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (int i = 0; i < Length; i++)
		{
			if (iterator > NumMenuOptions)
			{
				break;
			}
			OptionVect[iterator]->GetTransform().position = NewPosition;
			NewPosition.x += p_Game->ScreenSize.x * SeperationDistanceX;
			iterator++;
		}
		NewPosition.x = StartPosition.x;
		NewPosition.y -= p_Game->ScreenSize.y * SeperationDistanceY;
	}
}

void Selection::ResetSize(bool _isPlayer1, Character * _Player1, Character * _Player2)
{
	if (_isPlayer1)
	{
		OptionVect = _Player1->cardPile->Deck;
		NumMenuOptions = OptionVect.size() - 1;

	}
	else if (!_isPlayer1)
	{
		OptionVect = _Player2->cardPile->Deck;
		NumMenuOptions = OptionVect.size() - 1;
	}
	int iterator = 0;
	glm::vec3 NewPosition = StartPosition;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (int i = 0; i < Length; i++)
		{
			if (iterator > NumMenuOptions)
			{
				break;
			}
			OptionVect[iterator]->GetTransform().position = NewPosition;
			NewPosition.x += p_Game->ScreenSize.x * SeperationDistanceX;
			iterator++;
		}
		NewPosition.x = StartPosition.x;
		NewPosition.y -= p_Game->ScreenSize.y * SeperationDistanceY;
	}
}


void Selection::SelectOption(unsigned int _Option1, unsigned int _Option2)
{
	for (unsigned int i = 0; i < OptionVect.size(); ++i) {
		if (i != _Option1 || i != _Option2 || !playerOneIsOn || !playerTwoIsOn)
		{
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.03f, p_Game->ScreenSize.y * 0.06f, 1.0f);
		}
		if (i == _Option1 && MenuType == 1 && playerOneIsOn == true)
		{
			indicatorPlayer1->GetTransform().position = OptionVect[i]->GetTransform().position + glm::vec3(p_Game->ScreenSize.x * -0.03f, p_Game->ScreenSize.y * 0.12f, 0.1f);
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		if (i == _Option2 && MenuType == 2 && playerTwoIsOn == true)
		{
			indicatorPlayer2->GetTransform().position = OptionVect[i]->GetTransform().position + glm::vec3(p_Game->ScreenSize.x * 0.03f, p_Game->ScreenSize.y * 0.12f, 0.1f);
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		if (i == _Option1 && playerOneIsOn == true && MenuType == 0) 
		{
			indicatorPlayer1->GetTransform().position = OptionVect[i]->GetTransform().position + glm::vec3(p_Game->ScreenSize.x * -0.03f, p_Game->ScreenSize.y * 0.12f, 0.1f);
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		if (i == _Option2 && playerTwoIsOn == true && MenuType == 0)
		{
			indicatorPlayer2->GetTransform().position = OptionVect[i]->GetTransform().position + glm::vec3(p_Game->ScreenSize.x * 0.03f, p_Game->ScreenSize.y * 0.12f, 0.1f);
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
	}
}

void Selection::Process(Character * _Player1, Character * _Player2)
{
	//ResetRender();
	if (CInputManager::KeyArray['s'] == KEY_FIRST_PRESS)
	{
		playerOneIsOn = !playerOneIsOn;
	}
	if (CInputManager::KeySpecialArray[GLUT_KEY_DOWN] == KEY_FIRST_PRESS)
	{
		playerTwoIsOn = !playerTwoIsOn;
	}
	if (MenuType == 1 && OptionVect != _Player1->cardPile->Deck)
	{
		ResetSize(true, _Player1, _Player2);
	}
	if (MenuType == 2 && OptionVect != _Player2->cardPile->Deck)
	{
		ResetSize(false, _Player1, _Player2);
	}
	if (playerOneIsOn)
	{
		if (MenuType == 0 || MenuType == 1)
		{
			//could add more controls to the menu if needed.
			if (CInputManager::KeyArray['a'] == KEY_FIRST_PRESS) {
				DecrementMenu(1);
			}
			else if (CInputManager::KeyArray['d'] == KEY_FIRST_PRESS) {
				IncrementMenu(1);
			}
			else if (CInputManager::KeyArray['w'] == KEY_FIRST_PRESS) {
				if (_Player1->cardPile->Deck.size() < 10 && MenuType == 0)
				{
					//Selected card goes in deck or is removed
					AddCard(true, _Player1, _Player2);
					return;
				}
				else if (MenuType == 1)
				{
					RemoveCard(true, _Player1, _Player2);
					return;
				}
			}
		}
	}
	if (playerTwoIsOn)
	{
		if (MenuType == 0 || MenuType == 2)
		{
			if (CInputManager::KeySpecialArray[GLUT_KEY_LEFT] == KEY_FIRST_PRESS)
			{
				DecrementMenu(2);
			}
			else if (CInputManager::KeySpecialArray[GLUT_KEY_RIGHT] == KEY_FIRST_PRESS)
			{
				IncrementMenu(2);
			}
			else if (CInputManager::KeySpecialArray[GLUT_KEY_UP] == KEY_FIRST_PRESS)
			{
				if (_Player2->cardPile->Deck.size() < 10 && MenuType == 0)
				{
					//Selected card goes in deck or is removed
					AddCard(false, _Player1, _Player2);
					return;
				}
				else if (MenuType == 2)
				{
					RemoveCard(false, _Player1, _Player2);
					return;
				}
			}
		}
	}
	SelectOption(CurrentOptionPlayerOne, CurrentOptionPlayerTwo);
}

void Selection::Render()
{
	if (MenuType == 0)
	Start->Render();
	for (auto it : OptionVect) it->Render();
	if (MenuType == 0 && playerOneIsOn == true || MenuType == 1 && playerOneIsOn == true)
		indicatorPlayer1->Render();
	if (MenuType == 0 && playerTwoIsOn == true || MenuType == 2 && playerTwoIsOn == true)
		indicatorPlayer2->Render();
}

void Selection::RemoveCard(bool isPlayer1, Character* _Player1, Character* _Player2)
{
	if (isPlayer1 && _Player1->cardPile->Deck.size() > 0)
	{
		_Player1->cardPile->Deck.erase(_Player1->cardPile->Deck.begin() + CurrentOptionPlayerOne);
		CurrentOptionPlayerOne = 0;
		NumMenuOptions = _Player1->cardPile->Deck.size() - 1;
	}
	else if (!isPlayer1 && _Player2->cardPile->Deck.size() > 0)
	{
		_Player2->cardPile->Deck.erase(_Player2->cardPile->Deck.begin() + CurrentOptionPlayerTwo);
		CurrentOptionPlayerTwo = 0;
		NumMenuOptions = _Player2->cardPile->Deck.size() - 1;
	}
	
}

void Selection::AddCard(bool isPlayer1, Character* _Player1, Character* _Player2)
{
	if (isPlayer1)
	{
		Card* newCard = OptionVect[CurrentOptionPlayerOne]->clone();
		if (CheckCard(_Player1, newCard))
		{
			_Player1->cardPile->Deck.push_back(newCard);
		}
	}
	else if (!isPlayer1)
	{
		Card* newCard = OptionVect[CurrentOptionPlayerTwo]->clone();
		if (CheckCard(_Player2, newCard))
		{
			_Player2->cardPile->Deck.push_back(newCard);
		}
	}
}

bool Selection::CheckCard(Character* _Player, Card* _newCard)
{
	for (auto it : _Player->cardPile->Deck)
	{
		if (_newCard->GetName() == it->GetName())
		{
			return false;
		}
	}
	return true;
}

