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
	this->type = SIMPLETRI;
}

GameObject::~GameObject()
{
}

void GameObject::Tick()
{
}

void GameObject::Render()
{
	if (this->type == objectTypes::SIMPLETRI) {
		glBegin(GL_TRIANGLES);

		glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

		glVertex3f(this->simpleTriangleData.firstPoint.x, this->simpleTriangleData.firstPoint.y, this->simpleTriangleData.firstPoint.z);
		glVertex3f(this->simpleTriangleData.secondPoint.x, this->simpleTriangleData.secondPoint.y, this->simpleTriangleData.secondPoint.z);
		glVertex3f(this->simpleTriangleData.thirdPoint.x, this->simpleTriangleData.thirdPoint.y, this->simpleTriangleData.thirdPoint.z);

		glEnd();
	}
}
