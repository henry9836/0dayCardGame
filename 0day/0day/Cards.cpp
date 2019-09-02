#include "Cards.h"

AttackCard::AttackCard(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost, int _damage, AttackCard::CARDS _cardType)
{
	Console_OutputLog(to_wstring("Creating Card: " + _name), LOGINFO);
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
	damage = _damage;
	cardType = _cardType;
}

void AttackCard::Action(Character* _caster, Character* _target, Character* _otherPlayer)
{
	_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(_caster->selectedCardVector));
	_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + _caster->selectedCardVector);

	switch (cardType)
	{
		case AttackCard::FUZZER:
		{
			_caster->UpdateLines(-30.0f);
			_target->updateHP(-30.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::ROBOFIGHT:
		{
			_caster->UpdateLines(-10.0f);
			_target->updateHP(-5.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::ZERODAY:
		{
			_caster->UpdateLines(-100.0f);
			_otherPlayer->UpdateLines(-100.0f);

			int damage = 0;

			for (int i = 0; i < _caster->cardPile->Hand.size(); i++)
			{
				damage += _caster->cardPile->Hand.at(0)->cost;
				_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(0));
				_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin());
				i--;
			}
			for (int i = 0; i < _otherPlayer->cardPile->Hand.size(); i++)
			{
				damage += _otherPlayer->cardPile->Hand.at(0)->cost;
				_otherPlayer->cardPile->GY.push_back(_otherPlayer->cardPile->Hand.at(0));
				_otherPlayer->cardPile->Hand.erase(_otherPlayer->cardPile->Hand.begin());
				i--;
			}

			_target->updateHP((float)-damage * _caster->getDamageMult());
			break;
		}
		case AttackCard::DDOS:
		{
			_caster->UpdateLines(-70.0f);
			_target->updateHP(-75.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::SQL:
		{
			_caster->UpdateLines(-20.0f);
			_target->updateHP(-10.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::SKULL:
		{
			_caster->UpdateLines(-5.0f);

			int card = rand() % _caster->cardPile->Hand.size();

			_target->updateHP(-(_caster->cardPile->Hand.at(card)->cost) * _caster->getDamageMult());

			_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(card));
			_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + card);

			break;
		}
		case AttackCard::REDCIRCLE:
		{
			_caster->UpdateLines(-50.0f);
			_target->updateHP(-50.0f * _caster->getDamageMult());
			break;
		}
		default:
		{
			Console_OutputLog(L"attack default case", LOGINFO);
			break;
		}
	}


	delete _caster, _target, _otherPlayer;
}

DefenceCard::DefenceCard(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost, int _damage, DefenceCard::CARDS _cardType)
{
	Console_OutputLog(to_wstring("Creating Card: " + _name), LOGINFO);
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
	damage = _damage;
	cardType = _cardType;
}

void DefenceCard::Action(Character* _caster, Character* _target, Character* _otherPlayer)
{
	_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(_caster->selectedCardVector));
	_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + _caster->selectedCardVector);

	switch (cardType)
	{
		case DefenceCard::TAPE:
		{
			_caster->UpdateLines(-15.0f);
			_target->updateAccuracy(- _target->accuracy / 100.0f);
			break;
		}
		case DefenceCard::LOGIN:
		{
			//stop line generation
			break;
		}
		case DefenceCard::FIREWALL:
		{
			_caster->UpdateLines(-5.0f);
			_target->updateAccuracy(- _target->accuracy/2.0f);
			//until net attack
			break;
		}
		case DefenceCard::CREDS:
		{
			_caster->UpdateLines(-20.0f);
			_caster->UpdateLines(40.0f);
			_target->UpdateLines(-40.0f);
			break;
		}
		case DefenceCard::SUNGLASSES:
		{
			_caster->UpdateLines(-40.0f);
			_caster->MaxHPUpdate(25.0f);
			break;
		}
		default:
		{
			break;
		}
	}

	delete _caster, _target, _otherPlayer;

}

UtilityCard::UtilityCard(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost, int _damage, UtilityCard::CARDS _cardType)
{
	Console_OutputLog(to_wstring("Creating Card: " + _name), LOGINFO);
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
	damage = _damage;
	cardType = _cardType;
}

void UtilityCard::Action(Character* _caster, Character* _target, Character* _otherPlayer)
{
	_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(_caster->selectedCardVector));
	_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + _caster->selectedCardVector);
	switch (cardType)
	{
		case UtilityCard::SYSTEMRESET:
		{
			break;
		}
		case UtilityCard::FORKBOMB:
		{
			break;
		}
		case UtilityCard::REINFORCED:
		{
			break;
		}
		case UtilityCard::ENHNACED:
		{
			break;
		}
		case UtilityCard::ENUMERATION:
		{
			break;
		}
		case UtilityCard::ACCOUNT:
		{
			break;
		}
		case UtilityCard::SELFMODIFIYING:
		{
			break;
		}


	}
}
