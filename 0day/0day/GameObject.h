#pragma once
#include "Util.h"

class GameObject {
public:
	
	enum objectTypes {
		UNASSIGNEDTYPE,
		SIMPLETRI,
		SIMPLELINE,
		SIMPLEFAN
	};

	//Constructors
	GameObject(string _name);
	GameObject(SimpleTriangle _triangleData, glm::vec4 color, string _name); //Simple Triangle
	GameObject(SimpleLine _simpleLineData, glm::vec4 color, string _name); //Simple Line
	GameObject(SimpleFan _simpleFanData, glm::vec4 color, string _name); //Simple Fan
	~GameObject();

	void Tick();
	void Render();

	//Variables needed for all gameobjects
	glm::vec4 color;
	objectTypes type = UNASSIGNEDTYPE;
	string name = "Unnamed GameObject";
	vector<Scenes> assignedScenes;

	SimpleTriangle simpleTriangleData;
	SimpleLine simpleLineData;
	SimpleFan simpleFanData;
	
	

	glm::vec3 position;

};
