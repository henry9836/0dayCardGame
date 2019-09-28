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

	switch (cardType)
	{
		case AttackCard::FUZZER:
		{
			_target->updateHP(-30.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::ROBOFIGHT:
		{
			_target->updateHP(-5.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::ZERODAY:
		{
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
			_target->updateHP(-75.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::SQL:
		{
			_target->updateHP(-10.0f * _caster->getDamageMult());
			break;
		}
		case AttackCard::SKULL:
		{

			int card = rand() % _caster->cardPile->Hand.size() - 1;

			_target->updateHP(-(_caster->cardPile->Hand.at(card)->cost) * _caster->getDamageMult());

			_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(card));
			_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + card);

			break;
		}
		case AttackCard::REDCIRCLE:
		{
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

	switch (cardType)
	{
		case DefenceCard::TAPE:
		{
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
			_target->updateAccuracy(- _target->accuracy/2.0f);
			//until net attack
			break;
		}
		case DefenceCard::CREDS:
		{
			_caster->UpdateLines(40.0f);
			_target->UpdateLines(-40.0f);
			break;
		}
		case DefenceCard::SUNGLASSES:
		{
			_caster->MaxHPUpdate(25.0f);
			break;
		}
		default:
		{
			Console_OutputLog(L"defence default case", LOGINFO);
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
	switch (cardType)
	{
		case UtilityCard::SYSTEMRESET:
		{

			for (int i = 0; i < (signed int)_caster->cardPile->Hand.size(); i++)
			{
				damage += _caster->cardPile->Hand.at(0)->cost;
				_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(0));
				_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin());
				i--;
			}
			for (int i = 0; i < (signed int)_otherPlayer->cardPile->Hand.size(); i++)
			{
				damage += _otherPlayer->cardPile->Hand.at(0)->cost;
				_otherPlayer->cardPile->GY.push_back(_otherPlayer->cardPile->Hand.at(0));
				_otherPlayer->cardPile->Hand.erase(_otherPlayer->cardPile->Hand.begin());
				i--;
			}

			_caster->updateHP((float)(_caster->maxHP / 2.0f));
			_otherPlayer->updateHP((float)(_otherPlayer->maxHP / 2.0f));


			break;
		}
		case UtilityCard::FORKBOMB:
		{
			_caster->DrawACard();
			_caster->DrawACard();
			_otherPlayer->DrawACard();
			_otherPlayer->DrawACard();

			break;
		}
		case UtilityCard::REINFORCED:
		{
			_otherPlayer->damageMult += 0.1f * _otherPlayer->damageMult;
			break;
		}
		case UtilityCard::ENHNACED:
		{
			//double lines over next 5 seconds
			break;
		}
		case UtilityCard::ENUMERATION:
		{
			_caster->DrawACard();
			_caster->DrawACard();
			break;
		}
		case UtilityCard::ACCOUNT:
		{
			_otherPlayer->UpdateLines(40.0f);
			break;
		}
		case UtilityCard::SELFMODIFIYING:
		{
			int card = rand() % _caster->cardPile->Hand.size();
			_caster->UpdateLines((float)_caster->cardPile->Hand.at(card)->cost);
			_caster->cardPile->GY.push_back(_caster->cardPile->Hand.at(card));
			_caster->cardPile->Hand.erase(_caster->cardPile->Hand.begin() + card);//double check
			break;
		}
		default:
		{
			Console_OutputLog(L"utility default case", LOGINFO);
			break;
		}


	}
	delete _caster, _target, _otherPlayer;

}
