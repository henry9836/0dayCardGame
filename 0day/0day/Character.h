#include <iostream>
#pragma once


class Character
{
public:

	Character();
	~Character();
	virtual void updateHP(float damage) { currentHP += damage; }; 
	virtual void constantuUpdateLines(float deltaTime);
	virtual void UpdateLines(float Diffrence);
	virtual bool checkIfPlayable(float cost);

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

	AI();
	~AI();


private: 

	


};