#pragma once
#include "Util.h"
#include "MeshManager.h"

class CTextLabel;
class Game;

class GameObject {
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
		DEMO
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

#include "TextManager.h"
#include "GameManager.h"
