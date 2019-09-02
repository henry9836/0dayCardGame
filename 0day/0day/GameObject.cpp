#include "GameObject.h"

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
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), _transform->position);

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
	//auto MVP = game->camera.getVP() * cardData.ModelMatrix;
	int halfw = (int)game->ScreenSize.x / 2;
	int halfh = (int)game->ScreenSize.y / 2;
	auto MVP = glm::ortho<float>((float)-halfw, (float)halfw, (float)-halfh, (float)halfh, 0.1f, 1000.0f) * glm::translate(glm::mat4(), glm::vec3(0, 0, -1)) * ModelMatrix;

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

void RenderObject::SetTexture(GLuint _tex)
{
	this->texture = _tex;
}

void RenderObject::SetShader(GLuint _shader)
{
	this->shaderProgram = _shader;
}

void TickObject::Tick(float deltaTime, GameObject* _GameObject)
{
	//Console_OutputLog(L"Ticker", LOGINFO);
}

void RenderText::Render(Transform* _transform)
{
	text->Render();
}

Card::Card()
{
}

Card::Card(RenderClass * r, TickClass * t, Transform _trans, string _name, int _cost)
{
	transform = _trans;
	_r = r;
	_t = t;
	name = _name;
	cost = _cost;
}

Card::~Card()
{
}

GameObject::GameObject()
{
}

void RenderMenuText::Render(Transform* _transform)
{
	menu->Render();
}

void BarsTick::Tick(float deltaTime, GameObject* _gameObject)
{

}
