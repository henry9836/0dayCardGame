#pragma once
#include "Cards.h"
#include "Character.h"

class Selection
{
public:
	Selection(std::vector<Card*> _OptVect, glm::vec2 Pos, int _Length, float _SeperationDistanceX, float _SeperationDistanceY, Game* _Game, int _Menu);
	~Selection();
	void IncrementMenu(int _Player);
	void DecrementMenu(int _Player);
	int GetCurrentOpt() { return CurrentOption; };
	void ReplaceOption(int _OptIndex, std::string _OptionText);
	void SelectOption(unsigned int _Option1, unsigned int _Option2);
	void Process(Character* _Player1, Character* _Player2);
	void Render();

	private:
	std::vector<Card*> OptionVect;

	int MenuType;
	int NumMenuOptions;
	int CurrentOptionPlayerOne;
	int CurrentOptionPlayerTwo;
};