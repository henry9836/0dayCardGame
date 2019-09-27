#pragma once
#include "Cards.h"
#include "Character.h"

class Selection
{
public:
	Selection(std::vector<Card*> _OptVect, glm::vec3 _Pos, int _Length, float _SeperationDistanceX, float _SeperationDistanceY, Game * _Game, int _Menu, bool _playerOneIsOn, bool  _PlayerTwoIsOn);
	~Selection();
	void IncrementMenu(int _Player);
	void DecrementMenu(int _Player);
	void ResetRender();
	void ResetSize(bool _isPlayer, Character * _Player1, Character * _Player2);
	void SelectOption(unsigned int _Option1, unsigned int _Option2);
	void Process(Character* _Player1, Character* _Player2);
	void Render();
	void RemoveCard(bool isPlayer1, Character * _Player1, Character * _Player2);
	void AddCard(bool isPlayer1, Character * _Player1, Character * _Player2);

	private:
	std::vector<Card*> OptionVect;
	glm::vec3 StartPosition;
	Game* p_Game;
	int MenuType;
	int NumMenuOptions;
	int CurrentOptionPlayerOne;
	int CurrentOptionPlayerTwo;
	int Length;
	float SeperationDistanceX;
	float SeperationDistanceY;
	bool playerOneIsOn;
	bool playerTwoIsOn;
};