#include "GameObject.h"

GameObject::GameObject(string _name)
{
	
	Console_OutputLog(to_wstring("Creating GameObject But GameObject (\"" + _name + "\") Has No Type"), LOGWARN);
	this->name = _name;
	this->type = UNASSIGNEDTYPE;
}

GameObject::GameObject(SimpleTriangle _triangleData, glm::vec4 color, string _name)
{
	Console_OutputLog(to_wstring("Creating Simple Triangle Object: " + _name), LOGINFO);
	this->color = color;
	this->name = _name;
	this->simpleTriangleData = _triangleData;
}

GameObject::~GameObject()
{
}

void GameObject::Tick()
{
}

void GameObject::Render()
{
}
