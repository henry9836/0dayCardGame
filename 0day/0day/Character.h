#pragma once
#include <iostream>
#include "GameObject.h"
#include <algorithm>
#include <random>

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
	Character(CardPile* _cardPile);
	~Character();

	virtual void updateHP(float damage) { currentHP += damage; }; //implemet damage modifier
	virtual void constantuUpdateLines(float deltaTime);
	virtual void UpdateLines(float Diffrence);
	virtual bool checkIfPlayable(float cost);
	virtual float getHpBarPersent() { return currentHP / maxHP; };
	virtual float getLinesBatPersent() { return currentLines / maxlines; };
	float getDamageMult() { return damageMult; };
	virtual void updateAccuracy(float modifiyer) { accuracy += modifiyer; };
	virtual void MaxHPUpdate(float HP) { maxHP += HP; currentHP += HP; };
	virtual void DrawACard() { 
		if (cardPile->Hand.size() < 11) { 
			if (cardPile->Deck.size() > 0) {
				cardPile->Hand.push_back(cardPile->Deck.back());
				cardPile->Deck.pop_back();
			}
			else {
				Console_OutputLog(L"Cannot Deal Card As Deck Size is 0", LOGWARN);
			}
		} };

	CardPile* cardPile;

	void Render();
	void Tick(float deltaTime);

	//render function //deck
	int selectedCardVector = 0;
	
	const glm::vec3 defaultCardSize = glm::vec3(25.0f, 40.0f, 1.0f);
	float accuracy;
	float maxHP;
	float damageMult;
	float currentHP;
	float LinesMult = 1.0f;
	float drawcardThreshold = 1.0f;
	float drawcardTimer = 0.0f;
	float maxlines = 100.0f;
	float currentLines = 0.0f;

};

class Human : public Character
{
public:

	Human(CardPile* _cardPile) : Character(_cardPile)
	{
		float initalHP = 100.0f;
		float currentHP = initalHP;
		float currentLines = 35.0f;
		float damageMult = 1.0f;
		float LinesMult = 1.0f;
		float accuracy = 1.0f;
	};
	~Human();

};

class AI : public Character
{
public:

	AI(int Level, CardPile* _cardPile) : Character(_cardPile)
	{
		float initalHP = 100.0f + ((Level * 10) * (Level * 10));
		float currentHP = initalHP;
		float currentLines = 0.0f;
		float damageMult = 1.0f;
		float LinesMult = 1.0f;
		float rateOfLinesMult = Level * 0.001f;
		float accuracy = 1.0f;
	};
	~AI();

	void updateRateOfLinesMult(float deltaTime);

private: 

	float rateOfLinesMult;

};