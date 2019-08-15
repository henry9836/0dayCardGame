#include "GameObject.h"

GameObject::GameObject(string _name)
{
	Console_OutputLog(to_wstring("Creating GameObject But GameObject (\"" + _name + "\") Has No Type"), LOGWARN);
	this->name = _name;
	this->type = UNASSIGNEDTYPE;
}

GameObject::GameObject(BasicCard _cardData, string _name, vector<objectBehaviours> _behaviours)
{
	this->name = _name;
	this->cardData = _cardData;
	this->behaviours.clear();
	this->type = BASICCARD;
	for (size_t i = 0; i < _behaviours.size(); i++)
	{
		this->behaviours.push_back(_behaviours.at(i));
	}
	/*Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Pos = _Pos;
	VAO = MeshManager::GetMesh(_ObjectType)->VAO;
	IndicesCount = MeshManager::GetMesh(_ObjectType)->IndicesCount;
	Texture = MeshManager::GetMesh(_ObjectType)->Texture;
	Shader = MeshManager::GetMesh(_ObjectType)->Shader;
	Type = _ObjectType;*/
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

GameObject::GameObject(CTextLabel* _text, string _name, vector<objectBehaviours> _behaviours)
{
	this->type = TEXT;
	this->name = _name;
	this->behaviours.clear();
	this->text = _text;
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
		if (this->behaviours.at(i) == GameObject::DEMOCARD) {
			
		}
	}
}

void GameObject::Render(Game* game)
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
	else if (this->type == objectTypes::BASICCARD)
	{
		glUseProgram(cardData.Shader);

		//Binding the array
		glBindVertexArray(cardData.VAO);

		//Setting back face culling
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		glEnable(GL_CULL_FACE);

		//Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Setting and binding the correct texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cardData.Texture);

		//Sending the texture to the GPU via uniform
		glUniform1i(glGetUniformLocation(cardData.Shader, "tex"), 0);

		//Translating the cube (x,y,z)
		glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), cardData.Pos / 375.0f);

		//Y Rotation
		glm::mat4 RotateY =
			glm::rotate(
				glm::mat4(),
				glm::radians(cardData.Rotation.y),
				glm::vec3(0.0f, 1.0f, 0.0f)
			);

		//X Rotation
		glm::mat4 RotateX =
			glm::rotate(
				glm::mat4(),
				glm::radians(cardData.Rotation.x),
				glm::vec3(1.0f, 0.0f, 0.0f)
			);

		glm::mat4 RotationMatrix = RotateX * RotateY;
		glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), cardData.Scale);

		cardData.ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

		//glm::mat4 MVP = game->camera.getMVP(this->cardData.Pos, this->cardData.Scale, glm::mat4()) * cardData.ModelMatrix;
		//auto MVP = game->camera.proj * game->camera.view * cardData.ModelMatrix;
		auto MVP = glm::ortho<float>(-1, 1, -1, 1, 0.1f, 1000.0f) * glm::translate(glm::mat4(), glm::vec3(0, 0, -1));

		glUniformMatrix4fv(glGetUniformLocation(cardData.Shader, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(cardData.Shader, "model"), 1, GL_FALSE, glm::value_ptr(cardData.ModelMatrix));
		glUniform3fv(glGetUniformLocation(cardData.Shader, "camPos"), 1, glm::value_ptr(game->camera.camPos));
		//Drawing the entity
		glDrawElements(GL_TRIANGLES, cardData.IndicesCount, GL_UNSIGNED_INT, 0);

		//Disabling backface culling
		glDisable(GL_CULL_FACE);

		glDisable(GL_BLEND);

		//Clearing the vertex array
		glBindVertexArray(0);
		glUseProgram(0);
	}

	else if (this->type == objectTypes::TEXT) {
		this->text->Render();
	}

	else {
		Console_OutputLog(to_wstring("GameObject \"" + this->name + "\" cannot be rendered as it's type is either unassigned or unknown to the render function."), LOGWARN);
	}
}
