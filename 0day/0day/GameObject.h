#pragma once
#include "Util.h"
#include "MeshManager.h"

class CTextLabel;

class GameObject {
public:
	
	enum objectTypes {
		UNASSIGNEDTYPE,
		SIMPLETRI,
		SIMPLELINE,
		SIMPLEFAN,
		TEXT
	};

	enum objectBehaviours {
		NONE,
		DEMO
	};

	//Constructors
	GameObject(string _name);
	GameObject(SimpleTriangle _triangleData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours); //Simple Triangle
	GameObject(SimpleLine _simpleLineData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours); //Simple Line
	GameObject(SimpleFan _simpleFanData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours); //Simple Fan
	GameObject(CTextLabel* _text, string _name, vector<objectBehaviours> _behaviours);
	~GameObject();

	void Tick(float deltaTime);
	void Render();

	//Variables needed for all gameobjects
	glm::vec4 color;
	objectTypes type = UNASSIGNEDTYPE;
	string name = "Unnamed GameObject";
	vector<objectBehaviours> behaviours = { objectBehaviours::NONE };

	SimpleTriangle simpleTriangleData;
	SimpleLine simpleLineData;
	SimpleFan simpleFanData;
	CTextLabel* text;

	glm::vec3 position;

	bool demoMode = true;

private:
	unsigned IndicesCount;

	GLuint VAO;
	GLuint Shader;
	GLuint Texture;

	glm::vec3 Pos;
	glm::vec3 Scale;
	glm::vec3 Rotation;

	glm::mat4 ModelMatrix;
	glm::mat4 VPMatrix;

};

#include "TextManager.h"
