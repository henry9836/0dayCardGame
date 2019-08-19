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

class RenderObject : public RenderClass{
public:
	RenderObject(GLuint _VAO, unsigned int _indiceCount, GLuint _texture, Game* _game, GLuint _shaderProgram) : VAO(_VAO), indiceCount(_indiceCount), texture(_texture), game(_game), shaderProgram(_shaderProgram) {};
	
	virtual void Render(Transform* _transform);
	virtual void SetTexture(GLuint _tex);
	virtual void SetShader(GLuint _shader);

	GLuint VAO;
	unsigned int indiceCount;
	GLuint texture;
	Game* game;
	GLuint shaderProgram;

};

class TickClass {
public:
	virtual void Tick(float deltaTime) = 0;
};

class TickObject : public TickClass {
public:
	virtual void Tick(float deltaTime);
};

class GameObject {
public:
	GameObject(RenderClass* r, TickClass* t, Transform _trans) : _r(r), _t(t), transform(_trans) {};

	void Tick(float deltaTime) { _t->Tick(deltaTime); };
	void Render() { _r->Render(&transform); };

	void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	void SetShader(GLuint _shader) { _r->SetTexture(_shader); };

	Transform transform;
	RenderClass* _r;
	TickClass* _t;
};

/*

//Base Class For All Gameobjects
class GameObject {
	public:
		enum objectTypes { //All types of gameobjects
			UNASSIGNEDTYPE,
			SIMPLETRI,
			SIMPLELINE,
			SIMPLEFAN,
			TEXT,
			BASICCARD
		};

		GameObject(string _name);
		~GameObject();
		virtual void Hello();
		virtual void Tick(float deltaTime);
		virtual void Render(Game* game);
		
		Transform transform; //holds position, scale and rotation
		string name = "Unnamed Object";
		objectTypes type = UNASSIGNEDTYPE;
		glm::vec4 color;
};

class SimpleTri : public GameObject {
public:
	SimpleTri();
	~SimpleTri();

	SimpleTriangle simpleTriangleData;
	void Render(Game* game);
	void Tick(float deltaTime);
};

class SimpleL : public GameObject {
public:
	SimpleL();
	~SimpleL();

	SimpleLine simpleLineData;
	void Render(Game* game);
	void Tick(float deltaTime);
};

class Simplefan : public GameObject {
public:
	Simplefan();
	~Simplefan();

	SimpleFan simpleFanData;
	void Render(Game* game);
	void Tick(float deltaTime);
};

class Text : public GameObject {
public:
	Text();
	~Text();

	CTextLabel textData;
	void Render(Game* game);
	void Tick(float deltaTime);
};

class Basiccard : public GameObject {
public:
	Basiccard();
	~Basiccard();

	BasicCard cardData;
	void Render(Game* game);
	void Tick(float deltaTime);
};

*/
/*
class OldGameObject {
public:

	enum objectTypes {
		UNASSIGNEDTYPE,
		SIMPLETRI,
		SIMPLELINE,
		SIMPLEFAN,
		TEXT,
		BASICCARD
	};

	enum objectBehaviours {
		NONE,
		DEMO,
		DEMOCARD
	};

	//Constructors
	GameObject(string _name);
	GameObject(BasicCard _cardData, string _name, vector<objectBehaviours> _behaviours);//Basic Card
	GameObject(SimpleTriangle _triangleData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours); //Simple Triangle
	GameObject(SimpleLine _simpleLineData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours); //Simple Line
	GameObject(SimpleFan _simpleFanData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours); //Simple Fan
	GameObject(CTextLabel* _text, string _name, vector<objectBehaviours> _behaviours);
	~GameObject();

	void Tick(float deltaTime);
	void Render(Game* game);

	//Variables needed for all gameobjects
	glm::vec4 color;
	objectTypes type = UNASSIGNEDTYPE;
	string name = "Unnamed GameObject";
	vector<objectBehaviours> behaviours = { objectBehaviours::NONE };

	SimpleTriangle simpleTriangleData;
	SimpleLine simpleLineData;
	SimpleFan simpleFanData;
	BasicCard cardData;
	CTextLabel* text;

	glm::vec3 position;

	bool demoMode = true;

};
*/
#include "TextManager.h"
#include "GameManager.h"
