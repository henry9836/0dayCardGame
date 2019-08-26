#include "Cards.h"

AttackCard::AttackCard(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost, int _damage, AttackCard::CARDS _cardType)
{
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
	damage = _damage;
	cardType = _cardType;
}

void AttackCard::Action(Character* _caster, Character* _target)
{
	if (cardType == FUZZER)
	{
		_caster->UpdateLines(-30.0f);
		_target->updateHP(-30.0f);
	}


	delete _caster, _target;
}

DefenceCard::DefenceCard(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost, int _damage, DefenceCard::CARDS _cardType)
{
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
	damage = _damage;
	cardType = _cardType;
}

void DefenceCard::Action()
{
}

UtilityCard::UtilityCard(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost, int _damage, UtilityCard::CARDS _cardType)
{
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
	damage = _damage;
	cardType = _cardType;
}

void UtilityCard::Action()
{
}
