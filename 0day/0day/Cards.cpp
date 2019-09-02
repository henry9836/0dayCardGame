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
	_caster->GY.push_back(_caster->Hand.at(_caster->selectedCardVector));
	_caster->Hand.erase(_caster->Hand.begin() + _caster->selectedCardVector);

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

			for (int i = 0; i < _caster->Hand.size(); i++)
			{
				damage += _caster->Hand.at(0)->cost;
				_caster->GY.push_back(_caster->Hand.at(0));
				_caster->Hand.erase(_caster->Hand.begin());
				i--;
			}
			for (int i = 0; i < _otherPlayer->Hand.size(); i++)
			{
				damage += _otherPlayer->Hand.at(0)->cost;
				_otherPlayer->GY.push_back(_otherPlayer->Hand.at(0));
				_otherPlayer->Hand.erase(_otherPlayer->Hand.begin());
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

			int card = rand() % _caster->Hand.size();

			_target->updateHP(-(_caster->Hand.at(card)->cost) * _caster->getDamageMult());

			_caster->GY.push_back(_caster->Hand.at(card));
			_caster->Hand.erase(_caster->Hand.begin() + card);

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
	_caster->GY.push_back(_caster->Hand.at(_caster->selectedCardVector));
	_caster->Hand.erase(_caster->Hand.begin() + _caster->selectedCardVector);

	switch (cardType)
	{
		case DefenceCard::TAPE:
		{
			_caster->UpdateLines(-15.0f);
			_target->updateAccuracy(-0.01f);
			break;
		}
		case DefenceCard::LOGIN:
		{
			break;
		}
		case DefenceCard::FIREWALL:
		{
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
	_caster->GY.push_back(_caster->Hand.at(_caster->selectedCardVector));
	_caster->Hand.erase(_caster->Hand.begin() + _caster->selectedCardVector);

}
