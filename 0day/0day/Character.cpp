#include "Character.h"
Character::Character()
{
}


Character::Character(CardPile* _cardPile, float _health, GameObject* _gameObject, bool _isAI)
{
	cardPile = _cardPile;
	maxHP = _health;
	currentHP = maxHP;
	gameObject = _gameObject;
}

Character::~Character()
{
}

//dounstantly ticking up increacing lines/ modifiable by lines muiltplayer
void Character::constantuUpdateLines(float deltaTime)
{
	//AI cannot attack
	if (this->isAI && isStopped == true)
	{
		this->lineStopped += (deltaTime/60);

		if (this->lineStopped < 5.0f)
		{
			return;
		}
		this->lineStopped = 0.0f;
		this->isStopped = false;
	}

	//Generate extra lines
	if (!this->isAI && isGenerate == true)
	{
		this->generateLine += (deltaTime/60);

		if (this->generateLine >= 5.0f)
		{
			this->LinesMult = this->LinesMultInit;
			this->generateLine = 0.0f;
			this->isGenerate = false;
		}

	}

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
	for (size_t i = 0; i < cardPile->Hand.size(); i++)
	{
		cardPile->Hand.at(i)->Render();
	}
}

void Character::Tick(float deltaTime)
{
	constantuUpdateLines(deltaTime);

	drawcardTimer += deltaTime/60;

	if (drawcardTimer > drawcardThreshold) {
		DrawACard();
		drawcardTimer = 0;
	}

	if (isAI) {
		if (currentLines >= 100) {
			int c = rand() % 2;
			wcout << "Dealing " << baseDamage << " To Player" << endl;
			float tempdamage = damageMult;
			if (isAttackReduced == true)
			{
				tempdamage = damageMult / 2.0f;
				isAttackReduced = false;
			}
			if (c == 0 && playerOne->currentHP > 0) {
				playerOne->currentHP -= baseDamage * tempdamage;
				
			}
			else {
				playerTwo->currentHP -= baseDamage * tempdamage;
			}
			currentLines = 0;
		}
	}

}

void Character::Reset()
{
	accuracy = accuracyInit;
	maxHP = maxHPInit;
	damageMult = damageMultInit;
	currentHP = currentHPInit;
	LinesMult = LinesMultInit;
	drawcardThreshold = drawcardThresholdInit;
	drawcardTimer = drawcardTimerInit;
	maxlines = maxlinesInit;
	currentLines = currentLinesInit;
	baseDamage = baseDamageInit;
}

//THIS NEEDS TO BE UPDATE TO DESTORY STUFF SO NULLPTR AND DELETE EVERYTHING IN HERE
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

CardPile::CardPile(glm::vec3 _handPos)
{
	handPos = _handPos;
}

CardPile::~CardPile()
{
}

void CardPile::shuffleDeck()
{
	auto seed = std::default_random_engine{};
	std::shuffle(std::begin(Deck), std::end(Deck), seed);
}
