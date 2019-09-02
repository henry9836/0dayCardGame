#pragma once
#include "Util.h"
#include "MeshManager.h"

class CTextLabel;
class Game;

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
	virtual void Tick(float deltaTime) = 0;
};

class IdleTick : public TickClass {
public:
	virtual void Tick(float deltaTime) { return; };
};

class TickObject : public TickClass {
public:
	virtual void Tick(float deltaTime);
};

class DeckObject : public TickClass {
public:
	virtual void Tick(float deltaTime);
	//vector<auto>deck;

};

class GameObject {
public:
	GameObject();
	GameObject(RenderClass* r, TickClass* t, Transform _trans, string _name) : _r(r), _t(t), transform(_trans), name(_name) { Console_OutputLog(to_wstring("Creating GameObject: " + _name), LOGINFO); };

	virtual void Tick(float deltaTime) { _t->Tick(deltaTime); };
	virtual void Render() { _r->Render(&transform); };

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

protected:
	Transform transform;
	RenderClass* _r;
	TickClass* _t;
	string name;
};

class Card : public GameObject {
public:
	virtual enum CARDS {
		FUZZER,
		ROBOFIGHT,
		ZERODAY,
		DDOS,
		SQL,
		SKULL,
		REDCIRCLE
	};


	Card();
	Card(RenderClass* r, TickClass* t, Transform _trans, string _name, int _cost);
	~Card();

	virtual void Tick(float deltaTime) { _t->Tick(deltaTime); };
	virtual void Render() { _r->Render(&transform); };

	virtual void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	virtual void SetShader(GLuint _shader) { _r->SetTexture(_shader); };
	
	CARDS cardType;

	int cost = 10;
};

#include "TextManager.h"
#include "GameManager.h"
