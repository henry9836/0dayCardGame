#pragma once
#include <iostream>
#include "GameObject.h"

class Character : public GameObject
{
public:

	Character();
	~Character();
	virtual void updateHP(float damage) { currentHP += damage; }; //implemet damage modifier
	virtual void constantuUpdateLines(float deltaTime);
	virtual void UpdateLines(float Diffrence);
	virtual bool checkIfPlayable(float cost);
	virtual float getHpBarPersent() { return currentHP / maxHP; };

	vector<Card*> Deck;
	vector<Card*> Hand;
	vector<Card*> GY;

	void Render();
	void Tick();

	//render functionb //deck



protected:

	float maxHP;
	float currentHP;
	float currentLines;
	float damageMult;
	float LinesMult;


};

class Human : public Character
{
public:

	Human();
	~Human();
	


private: 

};

class AI : public Character
{
public:

	AI(int Level);
	~AI();

	void updateRateOfLinesMult(float deltaTime);

private: 

	float rateOfLinesMult;

};