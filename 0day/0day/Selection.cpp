#include "Selection.h"

Selection::Selection(std::vector<Card*> _OptVect, glm::vec3 _Pos, int _Length, float _SeperationDistanceX, float _SeperationDistanceY, Game * _Game, int _Menu)
{
	NumMenuOptions = 0;
	glm::vec3 StartPosition = _Pos;
	glm::vec3 NewPosition = _Pos;
	OptionVect = _OptVect;
	NumMenuOptions = _OptVect.size() - 1;
	MenuType = _Menu;
	int iterator;
	//Iterating through the provided option vect
	while (iterator <= NumMenuOptions)
	{
		for (unsigned int i = 0; i < _Length; i++)
		{
			if (iterator > NumMenuOptions)
			{
				break;
			}
			OptionVect[i]->GetTransform().position = NewPosition;
			NewPosition.x += _Game->ScreenSize.x * _SeperationDistanceX;
			iterator++;
		}
		NewPosition.x = StartPosition.x;
		NewPosition.y += _Game->ScreenSize.y * _SeperationDistanceY;
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
		if(CurrentOptionPlayerTwo)CurrentOptionPlayerTwo = NumMenuOptions;
		else --CurrentOptionPlayerTwo;
	}
}

void Selection::ResetSize(bool _isPlayer, Character * _Player1, Character * _Player2)
{
	if (_isPlayer)
	{
		OptionVect = _Player1->Deck;
	}
	else if (!_isPlayer)
	{
		OptionVect = _Player2->Deck;
	}
}


void Selection::SelectOption(unsigned int _Option1, unsigned int _Option2)
{
	for (unsigned int i = 0; i < OptionVect.size(); ++i) {
		if (i == _Option1 || i == _Option2) {
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x*0.05f, p_Game->ScreenSize.y*0.1f, 1.0f);
		}
		else {
			OptionVect[i]->GetTransform().scale = glm::vec3(p_Game->ScreenSize.x*0.03f, p_Game->ScreenSize.y*0.06f, 1.0f);
		}
	}
}

void Selection::Process(Character * _Player1, Character * _Player2)
{
	if (MenuType == 1 && OptionVect.size() != _Player1->Deck.size())
	{
		ResetSize(true, _Player1, _Player2);
	}
	else if (MenuType == 2 && OptionVect.size() != _Player2->Deck.size())
	{
		ResetSize(true, _Player1, _Player2);
	}
	if (MenuType == 0 || MenuType == 1)
	{
		//could add more controls to the menu if needed.
		if (CInputManager::KeySpecialArray[GLUT_KEY_UP] == KEY_FIRST_PRESS) {
			DecrementMenu(1);
		}
		else if (CInputManager::KeySpecialArray[GLUT_KEY_DOWN] == KEY_FIRST_PRESS) {
			IncrementMenu(1);
		}
		else if (CInputManager::KeyArray['\r'] == KEY_FIRST_PRESS) {
			if (_Player1->Deck.size() < 10 && MenuType == 0)
			{
				//Selected card goes in deck or is removed
				AddCard(true, _Player1, _Player2);
				return;
			}
			else if (MenuType == 2)
			{
				RemoveCard(false, _Player1, _Player2);
				return;
			}
		}
	}
	if (MenuType == 0 || MenuType == 2)
	{
		if (CInputManager::KeyArray['w'] == KEY_FIRST_PRESS)
		{
			DecrementMenu(2);
		}
		else if (CInputManager::KeyArray['s'] == KEY_FIRST_PRESS)
		{
			IncrementMenu(2);
		}
		else if (CInputManager::KeyArray['r'] == KEY_FIRST_PRESS)
		{
			if (_Player2->Deck.size() < 10 && MenuType == 0)
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
		_Player1->Deck.erase(_Player1->Deck.begin() + CurrentOptionPlayerOne);
	}
	else if (!isPlayer1)
	{
		_Player2->Deck.erase(_Player2->Deck.begin() + CurrentOptionPlayerTwo);
	}
}

void Selection::AddCard(bool isPlayer1, Character* _Player1, Character* _Player2)
{
	if (isPlayer1)
	{
		_Player1->Deck.push_back(OptionVect[CurrentOptionPlayerOne]);
	}
	else if (!isPlayer1)
	{
		_Player2->Deck.push_back(OptionVect[CurrentOptionPlayerTwo]);
	}
}
