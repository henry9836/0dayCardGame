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
	virtual float getLinesBatPersent() { return currentLines / maxlines; };
	float getDamageMult() { return damageMult; };
	virtual void updateAccuracy(float modifiyer) { accuracy += modifiyer; };
	virtual void MaxHPUpdate(float HP) { maxHP += HP; currentHP += HP; };

	vector<Card*> Deck;
	vector<Card*> Hand;
	vector<Card*> GY;

	void Render();
	void Tick(float deltaTime);

	//render function //deck
	int selectedCardVector = 0;
	glm::vec3 handPos;
	const glm::vec3 defaultCardSize = glm::vec3(40.0f, 60.0f, 1.0f);

protected:

	float maxlines = 100.0f;
	float maxHP;
	float currentHP;
	float currentLines;
	float damageMult;
	float LinesMult;
	float accuracy;

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