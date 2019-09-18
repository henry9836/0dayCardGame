#include "Character.h"
Character::Character()
{
}


Character::Character(vector<Card*> startingDeck)
{
	for (int i = 0; i < startingDeck.size(); i++)
	{
		Deck.push_back(startingDeck.at(0));
		Deck.push_back(startingDeck.at(0));
	}
	auto seed = std::default_random_engine{};
	std::shuffle(std::begin(Deck), std::end(Deck), seed);
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

void Character::Render()
{
	for (size_t i = 0; i < Hand.size(); i++)
	{
		Hand.at(i)->Render();
	}
}

void Character::Tick(float deltaTime)
{
	constantuUpdateLines(deltaTime);
}

Human::~Human()
{
}

AI::~AI()
{
}

void AI::updateRateOfLinesMult(float deltaTime)
{
	this->LinesMult += this->LinesMult * rateOfLinesMult * deltaTime;
}
