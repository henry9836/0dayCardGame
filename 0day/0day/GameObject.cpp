#include "GameObject.h"

GameObject::GameObject(string _name)
{
	
	Console_OutputLog(to_wstring("Creating GameObject But GameObject (\"" + _name + "\") Has No Type"), LOGWARN);
	this->name = _name;
	this->type = UNASSIGNEDTYPE;
}

GameObject::GameObject(SimpleTriangle _triangleData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours)
{
	Console_OutputLog(to_wstring("Creating Simple Triangle Object: " + _name), LOGINFO);
	this->color = color;
	this->name = _name;
	this->simpleTriangleData = _triangleData;
	this->type = SIMPLETRI;
	this->behaviours.clear();
	for (size_t i = 0; i < _behaviours.size(); i++)
	{
		this->behaviours.push_back(_behaviours.at(i));
	}
}

GameObject::GameObject(SimpleLine _simpleLineData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours)
{
	Console_OutputLog(to_wstring("Creating Simple Line Object: " + _name), LOGINFO);
	this->color = color;
	this->name = _name;
	this->simpleLineData = _simpleLineData;
	this->type = SIMPLELINE;
	this->behaviours.clear();
	for (size_t i = 0; i < _behaviours.size(); i++)
	{
		this->behaviours.push_back(_behaviours.at(i));
	}
}

GameObject::GameObject(SimpleFan _simpleFanData, glm::vec4 color, string _name, vector<objectBehaviours> _behaviours)
{
	Console_OutputLog(to_wstring("Creating Simple Triangle Fan Object: " + _name), LOGINFO);
	this->color = color;
	this->name = _name;
	this->simpleFanData = _simpleFanData;
	this->type = SIMPLEFAN;
	this->behaviours.clear();
	for (size_t i = 0; i < _behaviours.size(); i++)
	{
		this->behaviours.push_back(_behaviours.at(i));
	}
}

GameObject::~GameObject()
{

}

void GameObject::Tick(float deltaTime)
{
	for (size_t i = 0; i < this->behaviours.size(); i++)
	{
		if (this->behaviours.at(i) == GameObject::DEMO) {
			if (this->type == objectTypes::SIMPLELINE) {
				if (demoMode) {
					this->simpleLineData.secondPoint.x += (0.01f * deltaTime);
					this->simpleLineData.firstPoint.y -= (0.01f * deltaTime);
				}
				else {
					this->simpleLineData.secondPoint.x -= (0.01f * deltaTime);
					this->simpleLineData.firstPoint.y += (0.01f * deltaTime);
				}
				if (this->simpleLineData.secondPoint.x > 0.9f) {
					demoMode = false;
				}
				else if (this->simpleLineData.secondPoint.x < -0.9f) {
					demoMode = true;
				}
			}
		}
	}
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

	else if (this->type == objectTypes::SIMPLELINE) {
		glBegin(GL_LINES);

		glLineWidth(100.0f);

		glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

		glVertex3f(this->simpleLineData.firstPoint.x, this->simpleLineData.firstPoint.y, this->simpleLineData.firstPoint.z);
		glVertex3f(this->simpleLineData.secondPoint.x, this->simpleLineData.secondPoint.y, this->simpleLineData.secondPoint.z);

		glEnd();
	}

	else if (this->type == objectTypes::SIMPLEFAN) {
		glBegin(GL_TRIANGLE_FAN);

		glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

		glVertex3f(this->simpleFanData.firstPoint.x, this->simpleFanData.firstPoint.y, this->simpleFanData.firstPoint.z);
		for (size_t i = 0; i < this->simpleFanData.points.size(); i++)
		{
			glVertex3f(this->simpleFanData.points.at(i).x, this->simpleFanData.points.at(i).y, this->simpleFanData.points.at(i).z);
		}

		glEnd();
	}

	else {
		Console_OutputLog(to_wstring("GameObject \""+this->name+"\" cannot be rendered as it's type is either unassigned or unknown to the render function."),LOGWARN);
	}
}
