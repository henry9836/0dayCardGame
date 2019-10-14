#pragma once
#include <iostream>
#include <algorithm>
#include <random>

#include "GameObject.h"

class CardPile {
public:
	CardPile(glm::vec3 _handPos);
	~CardPile();
	vector<Card*> Deck;
	vector<Card*> Hand;
	vector<Card*> GY;

	glm::vec3 handPos;

	void shuffleDeck();
};

class Character : public GameObject
{
public:
	Character();
	Character(CardPile* _cardPile, float _health, GameObject* _gameObject, bool _isAI);
	~Character();

	virtual void updateHP(float damage) { currentHP += damage; }; //implemet damage modifier
	virtual void constantuUpdateLines(float deltaTime);
	virtual void UpdateLines(float Diffrence);
	virtual bool checkIfPlayable(float cost);
	virtual float getHpBarPersent() { return currentHP / maxHP; };
	virtual float getLinesBatPersent() { return currentLines / maxlines; };
	float getDamageMult() { return damageMult; };
	virtual void updateAccuracy(float modifiyer) { accuracy += modifiyer; };
	virtual void MaxHPUpdate(float HP) { maxHP = HP; currentHP = HP; };
	virtual void updateLevel(int _lvl) = 0;

	virtual void moveGYToDeck() {
		
		Console_OutputLog(L"Shuffling Graveyard into Deck", LOGINFO);

		for (size_t i = 0; i < cardPile->GY.size(); i++)
		{
			cardPile->Deck.push_back(cardPile->GY.at(i));
		}

		cardPile->GY.clear();

		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(cardPile->Deck.begin(), cardPile->Deck.end(), g);

	};

	virtual void DrawACard() { 
		if (cardPile->Hand.size() < 10) {
			if (cardPile->Deck.size() > 0) {
				cardPile->Hand.push_back(cardPile->Deck.back());
				cardPile->Deck.pop_back();
			}
			else {
				moveGYToDeck();
				//Console_OutputLog(L"Cannot Deal Card As Deck Size is 0", LOGWARN);
			}
		}
	};

	CardPile* cardPile;

	void Render();
	void Tick(float deltaTime);
	void Reset();

	//render function //deck
	int selectedCardVector = 0;
	
	const glm::vec3 defaultCardSize = glm::vec3(25.0f, 40.0f, 1.0f);
	float accuracy = 1.0f;;
	float maxHP = 100.0f;
	float damageMult = 1.0f;
	float currentHP;
	float LinesMult = 0.25f;
	float drawcardThreshold = 2.0f;
	float drawcardTimer = 0.0f;
	float maxlines = 100.0f;
	float currentLines = 0.0f;
	float baseDamage = 17.5f;
	float lineStopped = 0.0f;
	float generateLine = 0.0f;
	GameObject* gameObject = nullptr;
	Character* playerOne = nullptr;
	Character* playerTwo = nullptr;
	bool isAI = false;
	bool isAttackReduced = false;
	bool isStopped = false;
	bool isGenerate = false;
	

	float accuracyInit = 1.0f;
	float maxHPInit = 100.0f;
	float damageMultInit = 1.0f;
	float currentHPInit = 100.0f;
	float LinesMultInit = LinesMult;
	float drawcardThresholdInit = 1.0f;
	float drawcardTimerInit = 0.0f;
	float maxlinesInit = 100.0f;
	float currentLinesInit = 0.0f;
	float baseDamageInit = 2.0f;

};

class Human : public Character
{
public:

	Human(CardPile* _cardPile, float _health, GameObject* _gameObject, bool _isAI) : Character(_cardPile, _health, _gameObject, _isAI)
	{

	};
	~Human();

	void updateLevel(int _lvl) {};

};

class AI : public Character
{
public:

	AI(int Level, CardPile* _cardPile, float _health, GameObject* _gameObject, bool _isAI, Character* _playerOne, Character* _playerTwo) : Character(_cardPile, _health, _gameObject, _isAI)
	{
		isAI = _isAI;
		playerOne = _playerOne;
		playerTwo = _playerTwo;
	};
	~AI();

	void updateRateOfLinesMult(float deltaTime);
	void updateLevel(int _lvl) {
		rateOfLinesMult = _lvl * 0.001f;
		MaxHPUpdate(100.0f + ((_lvl * 10) * (_lvl * 10)));
		baseDamage *= 1.05f;
	};


	GameObject* gameObject = nullptr;



private: 

	float rateOfLinesMult = 1.0f;

};