#include "GameObject.h"



/*
GameObject::GameObject(string _name)
{
	Console_OutputLog(to_wstring("Creating GameObject But GameObject (\"" + _name + "\") Has No Type"), LOGWARN);
	this->name = _name;
	this->type = UNASSIGNEDTYPE;
}

GameObject::~GameObject()
{

}

void GameObject::Tick(float deltaTime)
{
	
}

void GameObject::Render(Game* game)
{

	Console_OutputLog(to_wstring("GameObject \"" + this->name + "\" cannot be rendered as it's type does not have a unique render function"), LOGWARN);
}

void GameObject::Hello()
{
	Console_OutputLog(to_wstring("Hello World :) - " + this->name), LOGINFO);
}

SimpleTri::SimpleTri()
{
	this->type = objectTypes::SIMPLETRI;
}

SimpleTri::~SimpleTri()
{
}

void SimpleTri::Render(Game* game)
{
	glBegin(GL_TRIANGLES);

	glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

	glVertex3f(this->simpleTriangleData.firstPoint.x, this->simpleTriangleData.firstPoint.y, this->simpleTriangleData.firstPoint.z);
	glVertex3f(this->simpleTriangleData.secondPoint.x, this->simpleTriangleData.secondPoint.y, this->simpleTriangleData.secondPoint.z);
	glVertex3f(this->simpleTriangleData.thirdPoint.x, this->simpleTriangleData.thirdPoint.y, this->simpleTriangleData.thirdPoint.z);

	glEnd();
}

void SimpleTri::Tick(float deltaTime)
{
}

SimpleL::SimpleL()
{
}

SimpleL::~SimpleL()
{
}

void SimpleL::Render(Game* game)
{
	glBegin(GL_LINES);

	glLineWidth(100.0f);

	glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

	glVertex3f(this->simpleLineData.firstPoint.x, this->simpleLineData.firstPoint.y, this->simpleLineData.firstPoint.z);
	glVertex3f(this->simpleLineData.secondPoint.x, this->simpleLineData.secondPoint.y, this->simpleLineData.secondPoint.z);

	glEnd();
}

void SimpleL::Tick(float deltaTime)
{
}

Simplefan::Simplefan()
{
}

Simplefan::~Simplefan()
{
}

void Simplefan::Render(Game* game)
{
	glBegin(GL_TRIANGLE_FAN);

	glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

	glVertex3f(this->simpleFanData.firstPoint.x, this->simpleFanData.firstPoint.y, this->simpleFanData.firstPoint.z);
	for (size_t i = 0; i < this->simpleFanData.points.size(); i++)
	{
		glVertex3f(this->simpleFanData.points.at(i).x, this->simpleFanData.points.at(i).y, this->simpleFanData.points.at(i).z);
	}

	glEnd();
}

void Simplefan::Tick(float deltaTime)
{
}

Text::Text()
{

}

Text::~Text()
{

		//Setting back face culling
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

void Text::Render(Game* game)
{
	this->textData.Render();
}

void Text::Tick(float deltaTime)
{
}

Basiccard::Basiccard()
{
}

		//Translating the cube (x,y,z)
		glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), cardData.Pos);

void Basiccard::Render(Game* game)
{
	glUseProgram(cardData.Shader);

		//X Rotation
		glm::mat4 RotateX =
			glm::rotate(
				glm::mat4(),
				glm::radians(cardData.Rotation.x),
				glm::vec3(1.0f, 0.0f, 0.0f)
			);
		//Z Rotation
		glm::mat4 RotateZ =
			glm::rotate(
				glm::mat4(),
				glm::radians(cardData.Rotation.z),
				glm::vec3(0.0f, 0.0f, 1.0f)
			);

		glm::mat4 RotationMatrix = RotateX * RotateY * RotateZ;
		glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), cardData.Scale);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glm::mat4 MVP = game->camera.getMVP(this->cardData.Pos, this->cardData.Scale, glm::mat4()) * cardData.ModelMatrix;
		//auto MVP = game->camera.getVP() * cardData.ModelMatrix;
		int halfw = game->ScreenSize.x / 2;
		int halfh = game->ScreenSize.y / 2;
		auto MVP = glm::ortho<float>(-halfw, halfw, -halfh, halfh, 0.1f, 1000.0f) * glm::translate(glm::mat4(), glm::vec3(0, 0, -1)) * cardData.ModelMatrix;

		glUniformMatrix4fv(glGetUniformLocation(cardData.Shader, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(cardData.Shader, "model"), 1, GL_FALSE, glm::value_ptr(cardData.ModelMatrix));
		//Drawing the entity
		glDrawElements(GL_TRIANGLES, cardData.IndicesCount, GL_UNSIGNED_INT, 0);

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

void Basiccard::Tick(float deltaTime)
{

}

*/

void RenderObject::Render(Transform* _transform)
{
	glUseProgram(this->shaderProgram);

	//Binding the array
	glBindVertexArray(this->VAO);

	//Setting back face culling
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Setting and binding the correct texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	//Sending the texture to the GPU via uniform
	glUniform1i(glGetUniformLocation(this->shaderProgram, "tex"), 0);

	//Translating the cube (x,y,z)
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), _transform->position / 400.f);

	//Y Rotation
	glm::mat4 RotateY =
		glm::rotate(
			glm::mat4(),
			glm::radians(_transform->rotation.y),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

	//X Rotation
	glm::mat4 RotateX =
		glm::rotate(
			glm::mat4(),
			glm::radians(_transform->rotation.x),
			glm::vec3(1.0f, 0.0f, 0.0f)
		);
	//Z Rotation
	glm::mat4 RotateZ =
		glm::rotate(
			glm::mat4(),
			glm::radians(_transform->rotation.z),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);

	glm::mat4 RotationMatrix = RotateX * RotateY * RotateZ;
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), _transform->scale);

	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

	//glm::mat4 MVP = game->camera.getMVP(this->cardData.Pos, this->cardData.Scale, glm::mat4()) * cardData.ModelMatrix;
	auto MVP = cam->getVP() * ModelMatrix;
	//auto MVP = glm::ortho<float>(-1, 1, -1, 1, 0.1f, 1000.0f) * glm::translate(glm::mat4(), glm::vec3(0, 0, -1));

	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	//Drawing the entity
	glDrawElements(GL_TRIANGLES, this->indiceCount, GL_UNSIGNED_INT, 0);

	//Disabling backface culling
	glDisable(GL_CULL_FACE);

	glDisable(GL_BLEND);

	//Clearing the vertex array
	glBindVertexArray(0);
	glUseProgram(0);
}

void TickObject::Tick(float deltaTime)
{
	Console_OutputLog(L"Ticker", LOGINFO);
}
