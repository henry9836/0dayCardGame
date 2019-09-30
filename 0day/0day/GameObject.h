#pragma once
#include "Util.h"
#include "MeshManager.h"


class CMenu;
class CTextLabel;
class Game;
class GameObject;
class Character;

class RenderClass {
public:
	virtual void Render(Transform* _transform) = 0;
	virtual void SetTexture(GLuint _tex) = 0;
	virtual void SetShader(GLuint _shader) = 0;
};

class NoRender : public RenderClass {

};

class RenderObject : public RenderClass{
public:
	RenderObject();
	RenderObject(std::shared_ptr<MESH> _mesh, GLuint _texture, Game* _game, GLuint _shaderProgram) : VAO(_mesh->VAO), indiceCount(_mesh->IndicesCount), texture(_texture), game(_game), shaderProgram(_shaderProgram) {};
	
	virtual void Render(Transform* _transform);
	virtual void SetTexture(GLuint _tex);
	virtual void SetShader(GLuint _shader);

	GLuint VAO;
	unsigned int indiceCount;
	GLuint texture;
	Game* game;
	GLuint shaderProgram;

};

class RenderMenuText : public RenderClass
{
public:
	RenderMenuText(CMenu* _menu) : menu(_menu) {};

	virtual void Render(Transform* _transform);
	virtual void SetTexture(GLuint _tex) {};
	virtual void SetShader(GLuint _shader) {};

	CMenu* menu;
};

class RenderText : public RenderClass {
public:
	RenderText(CTextLabel* _text) : text(_text) {};

	virtual void Render(Transform* _transform);
	virtual void SetTexture(GLuint _tex) {};
	virtual void SetShader(GLuint _shader) {};

	CTextLabel* text;
};

class TickClass {
public:
	virtual void Tick(float deltaTime , GameObject* _gameObject) = 0;
};

class IdleTick : public TickClass {
public:
	virtual void Tick(float deltaTime, GameObject* _gameObject) { return; };
};

class TickObject : public TickClass {
public:
	virtual void Tick(float deltaTime, GameObject* _gameObject);
};

class DeckObject : public TickClass {
public:
	virtual void Tick(float deltaTime, GameObject* _gameObject);
	//vector<auto>deck;

};

class GameObject {
public:
	GameObject();
	GameObject(RenderClass* r, TickClass* t, Transform _trans, string _name) : _r(r), _t(t), transform(_trans), name(_name) { Console_OutputLog(to_wstring("Creating GameObject: " + _name), LOGINFO); };

	virtual void Tick(float deltaTime, GameObject* _gameObject) { _t->Tick(deltaTime, _gameObject); };
	virtual void Render() { _r->Render(&transform); };

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

	

	Transform& GetTransform() { return transform; };
	
protected:
	Transform transform;
	RenderClass* _r;
	TickClass* _t;
	
	string name;
};

class Card : public GameObject {
public:
	Card();
	Card(RenderClass* r, TickClass* t, Transform _trans, string _name, int _cost);
	~Card();

	virtual void Tick(float deltaTime, GameObject* _gameObject) { _t->Tick(deltaTime, _gameObject); };
	virtual void Render() { _r->Render(&transform); };

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };
	
	virtual void Action(Character* _caster, Character* _target, Character* _otherPlayer);

	virtual Card* clone() const = 0;

	string GetName() { return name; };

	int cost = 10;
};

#include "TextManager.h"
#include "Menu.h"
#include "GameManager.h"
#include "Character.h"
