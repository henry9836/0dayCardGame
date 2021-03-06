#include "Bars.h"

BarsRender::BarsRender(std::shared_ptr<MESH> _mesh, GLuint _texture, Game* _game, GLuint _shaderProgram, Character* _Characterptr, bool _isHealthBar)
{
	VAO = _mesh->VAO;
	indiceCount = _mesh->IndicesCount;
	texture = _texture;
	game = _game;
	shaderProgram = _shaderProgram;
	VBO = _mesh->VBO;
	isHealthBar = _isHealthBar;
	characterPtr = _Characterptr;
	Vertices = _mesh->Vertices;
	barInfo = new CTextLabel("INFO", Utility::NormalFontString.data(), glm::vec2(0, 0), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, _game);
}

BarsRender::~BarsRender()
{
	game = nullptr;
	characterPtr = nullptr;
	Vertices.clear();
	delete barInfo;
	barInfo = nullptr;
}


void BarsRender::Render(Transform * _transform)
{
	barInfo->SetPosition(glm::vec2(_transform->position.x + game->ScreenSize.x * -0.01f, _transform->position.y + game->ScreenSize.y * -0.005f));
	
	float Percentage;
	if (isHealthBar)
	{
		Percentage = characterPtr->getHpBarPersent();
		barInfo->SetText(std::to_string((int)characterPtr->currentHP) + " / " + std::to_string((int)characterPtr->maxHP));
	}
	else
	{
		Percentage = characterPtr->getLinesBatPersent();
		barInfo->SetText(std::to_string((int)characterPtr->currentLines) + " / " + std::to_string((int)characterPtr->maxlines));
	}
	
	ChangingVertices(Percentage);
	
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
	barInfo->Render();
}

void BarsRender::ChangingVertices(float _Value)
{
	float Percentage =_Value * 2;
	std::vector<GLfloat> newVertices = Vertices;
	for (int iVertex = 16; iVertex < (signed int)Vertices.size(); iVertex += 8)
	{
		newVertices[iVertex] = Percentage - Vertices[iVertex];
	}
	//Binding and Setting the buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(GLfloat), &newVertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
