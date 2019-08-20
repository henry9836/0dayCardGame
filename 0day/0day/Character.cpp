#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

//dounstantly ticking up increacing lines/ modifiable by lines muiltplayer
void Character::constantuUpdateLines(float deltaTime)
{
	if (this->currentLines < 100.0f)
	{
		this->currentLines += deltaTime * LinesMult;
	}

	if (this->currentLines > 100.0f)
	{
		this->currentLines = 100.0f;
	}
	
}

//call with -30 if playiing a csard that costs 30 will subtract 30 from current lines
void Character::UpdateLines(float Diffrence)
{
	if (Diffrence < 0)
	{
		if (this->currentLines * -1 > Diffrence)
		{
			this->currentLines = 0.0f;
		}
		else
		{
			this->currentLines += Diffrence;
		}
	}
	else
	{
		this->currentLines += Diffrence;
		if (this->currentLines > 100.0f)
		{
			this->currentLines = 100.0f;
		}
	}

}

bool Character::checkIfPlayable(float cost)
{
	bool playable = true;

	if (currentLines < cost)
	{
		playable = false;
	}

	return(playable);

}

Human::Human()
{
	float currentHP;
	float currentLines;
	float damageMult;
	float LinesMult;
	float initalHP;
}

Human::~Human()
{
}

AI::AI()
{
}

AI::~AI()
{
}
