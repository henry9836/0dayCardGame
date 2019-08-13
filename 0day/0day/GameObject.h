#pragma once
#include "Util.h"

class GameObject {
public:
	
	enum objectTypes {
		UNASSIGNEDTYPE,
		SIMPLETRI
	};

	//Constructors
	GameObject(string _name);
	GameObject(SimpleTriangle _triangleData, glm::vec4 color, string _name); //Simple Triangle
	~GameObject();

	void Tick();
	void Render();

	//Variables needed for all gameobjects
	glm::vec4 color;
	objectTypes type = UNASSIGNEDTYPE;
	string name = "Unnamed GameObject";
	vector<Scenes> assignedScenes;

	SimpleTriangle simpleTriangleData;
	
	

	glm::vec3 position;

};
