#pragma once

class Character
{
public:

	Character();
	~Character();
	virtual void updateHP(float damage) { currentHP += damage; }; //I fixed yr semicolms :)

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