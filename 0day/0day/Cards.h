#pragma once
#include "Util.h"
#include "GameObject.h"
#include "Character.h"

class Character;

class AttackCard : public Card {
public:
	enum CARDS {
		FUZZER,
		ROBOFIGHT,
		ZERODAY,
		DDOS,
		SQL,
		SKULL,
		REDCIRCLE
	};

	AttackCard(RenderClass* r, TickClass* t, Transform _trans, string _name, int _cost, int _damage, AttackCard::CARDS _cardType);
	virtual void Tick(float deltaTime, GameObject* _gameObject) { _t->Tick(deltaTime, _gameObject); };
	virtual void Render() { 
		_r->Render(&transform); 
		//_rr->Render(&transform);
	};
	void Action(Character* _caster, Character* _target, Character* _otherPlayer);

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

	int damage = 0;
	AttackCard::CARDS cardType = CARDS::FUZZER;

protected:
	RenderClass* _rr;
};

class DefenceCard : public Card {
public:
	enum CARDS {
		TAPE,
		LOGIN,
		FIREWALL,
		CREDS,
		SUNGLASSES
	};

	DefenceCard(RenderClass* r, TickClass* t, Transform _trans, string _name, int _cost, int _damage, DefenceCard::CARDS _cardType);
	virtual void Tick(float deltaTime, GameObject* _gameObject) { _t->Tick(deltaTime, _gameObject); };
	virtual void Render() {
		_r->Render(&transform);
		//_rr->Render(&transform);
	};
	void Action(Character* _caster, Character* _target, Character* _otherPlayer);

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

	int damage = 0;
	DefenceCard::CARDS cardType = CARDS::TAPE;

protected:
	RenderClass* _rr;
};

class UtilityCard : public Card {
public:
	enum CARDS {
	SYSTEMRESET,
	FORKBOMB,
	REINFORCED,
	ENHNACED,
	ENUMERATION,
	ACCOUNT,
	SELFMODIFIYING
	};

	UtilityCard(RenderClass* r, TickClass* t, Transform _trans, string _name, int _cost, int _damage, UtilityCard::CARDS _cardType);
	virtual void Tick(float deltaTime, GameObject* _gameObject) { _t->Tick(deltaTime, _gameObject); };
	virtual void Render() {
		_r->Render(&transform);
		//_rr->Render(&transform);
	};
	void Action(Character* _caster, Character* _target, Character* _otherPlayer);

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

	int damage = 0;
	UtilityCard::CARDS cardType = CARDS::SYSTEMRESET;

protected:
	RenderClass* _rr;
};