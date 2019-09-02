#pragma once
#include "Util.h"
#include "MeshManager.h"


class CMenu;
class CTextLabel;
class Game;

class RenderClass {
public:
	virtual void Render(Transform* _transform) = 0;
	virtual void SetTexture(GLuint _tex) = 0;
	virtual void SetShader(GLuint _shader) = 0;
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
	virtual void Tick(float deltaTime) = 0;
};

class MenuTick : public TickClass
{
public:
	virtual void Tick(float) { return; };
};

class IdleTick : public TickClass {
public:
	virtual void Tick(float deltaTime) { return; };
};

class TickObject : public TickClass {
public:
	virtual void Tick(float deltaTime);
};

class GameObject {
public:
	GameObject(RenderClass* r, TickClass* t, Transform _trans, string _name) : _r(r), _t(t), transform(_trans), name(_name) { Console_OutputLog(to_wstring("Creating GameObject: " + _name), LOGINFO); };

	void Tick(float deltaTime) { _t->Tick(deltaTime); };
	void Render() { _r->Render(&transform); };

	void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

	Transform transform;
	RenderClass* _r;
	TickClass* _t;
	string name;
};

#include "TextManager.h"
#include "Menu.h"
#include "GameManager.h"
