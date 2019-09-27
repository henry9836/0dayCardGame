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
	int iterator = 0;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (unsigned int i = 0; i < _Length; i++)
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

void Selection::DecrementMenu(int _Player)
{
	if (_Player == 1)
	{
		if (CurrentOptionPlayerOne == 0) CurrentOptionPlayerOne = NumMenuOptions;
		else --CurrentOptionPlayerOne;
	}
	else if (_Player == 2)
	{
		if(CurrentOptionPlayerTwo == 0) CurrentOptionPlayerTwo = NumMenuOptions;
		else --CurrentOptionPlayerTwo;
	}
}

void Selection::ResetRender()
{
	glm::vec3 NewPosition = StartPosition;
	int iterator = 0;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (unsigned int i = 0; i < Length; i++)
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

void Selection::ResetSize(bool _isPlayer, Character * _Player1, Character * _Player2)
{
	if (_isPlayer)
	{
		OptionVect = _Player1->cardPile->Deck;

	}
	else if (!_isPlayer)
	{
		OptionVect = _Player2->cardPile->Deck;
	}
	int iterator = 0;
	glm::vec3 NewPosition = StartPosition;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (unsigned int i = 0; i < Length; i++)
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
		if (i == _Option1 && MenuType == 1 && playerOneIsOn == true)
		{
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		else if (i == _Option2 && MenuType == 2 && playerTwoIsOn == true)
		{
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		else if (i == _Option1 && playerOneIsOn == true && MenuType == 0) 
		{
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		else if (i == _Option2 && playerTwoIsOn == true && MenuType == 0)
		{
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.05f, p_Game->ScreenSize.y * 0.1f, 1.0f);
		}
		else 
		{
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x * 0.03f, p_Game->ScreenSize.y * 0.06f, 1.0f);
		}
	}
}

void Selection::Process(Character * _Player1, Character * _Player2)
{
	//ResetRender();
	if (CInputManager::KeySpecialArray[GLUT_KEY_DOWN] == KEY_FIRST_PRESS)
	{
		playerOneIsOn = !playerOneIsOn;
	}
	if (CInputManager::KeyArray['s'] == KEY_FIRST_PRESS)
	{
		playerTwoIsOn = !playerTwoIsOn;
	}
	if (MenuType == 1 && OptionVect.size() != _Player1->cardPile->Deck.size())
	{
		ResetSize(true, _Player1, _Player2);
	}
	else if (MenuType == 2 && OptionVect.size() != _Player2->cardPile->Deck.size())
	{
		ResetSize(true, _Player1, _Player2);
	}
	if (playerOneIsOn)
	{
		if (MenuType == 0 || MenuType == 1)
		{
			//could add more controls to the menu if needed.
			if (CInputManager::KeySpecialArray[GLUT_KEY_LEFT] == KEY_FIRST_PRESS) {
				DecrementMenu(1);
			}
			else if (CInputManager::KeySpecialArray[GLUT_KEY_RIGHT] == KEY_FIRST_PRESS) {
				IncrementMenu(1);
			}
			else if (CInputManager::KeyArray['\r'] == KEY_FIRST_PRESS) {
				if (_Player1->cardPile->Deck.size() < 10 && MenuType == 0)
				{
					//Selected card goes in deck or is removed
					AddCard(true, _Player1, _Player2);
					return;
				}
				else if (MenuType == 2)
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
			if (CInputManager::KeyArray['a'] == KEY_FIRST_PRESS)
			{
				DecrementMenu(2);
			}
			else if (CInputManager::KeyArray['d'] == KEY_FIRST_PRESS)
			{
				IncrementMenu(2);
			}
			else if (CInputManager::KeyArray['w'] == KEY_FIRST_PRESS)
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
	for (auto it : OptionVect) it->Render();
}

void Selection::RemoveCard(bool isPlayer1, Character* _Player1, Character* _Player2)
{
	if (isPlayer1)
	{
		_Player1->cardPile->Deck.erase(_Player1->cardPile->Deck.begin() + CurrentOptionPlayerOne);
		CurrentOptionPlayerOne = 0;
	}
	else if (!isPlayer1)
	{
		_Player2->cardPile->Deck.erase(_Player2->cardPile->Deck.begin() + CurrentOptionPlayerTwo);
		CurrentOptionPlayerTwo = 0;
	}
}

void Selection::AddCard(bool isPlayer1, Character* _Player1, Character* _Player2)
{
	if (isPlayer1)
	{
		Card* newCard = OptionVect[CurrentOptionPlayerOne]->clone();
		_Player1->cardPile->Deck.push_back(newCard);
	}
	else if (!isPlayer1)
	{
		Card* newCard = OptionVect[CurrentOptionPlayerOne]->clone();
		_Player2->cardPile->Deck.push_back(newCard);;
	}
}