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


void Selection::SelectOption(unsigned int _Option1, unsigned int _Option2)
{
	for (unsigned int i = 0; i < OptionVect.size(); ++i) {
		if (i == _Option1 || i == _Option2) {
			OptionVect[i]->GetTransform().scale = glm::vec3(,,);
		}
		else {
			OptionVect[i]->GetTransform().scale = glm::vec3(,,) ;
		}
	}
}

void Selection::Process(Character * _Player1, Character * _Player2)
{
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
			if (_Player1->Deck.size() < 10)
			{
				//Selected card goes in deck or is removed
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
			if (_Player2->Deck.size() < 10)
			{
				//Selected card goes in deck or is removed
				return;
			}
		}
	}
	SelectOption(CurrentOptionPlayerOne);
	SelectOption(CurrentOptionPlayerTwo);
}

void Selection::Render()
{
	for (auto it : OptionVect) it->Render();
}
