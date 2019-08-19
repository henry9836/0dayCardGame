#pragma once

//header files
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <SOIL.h>
#include <glm.hpp>
#include <glut.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>
#include <iostream>
//
//solution header files

#include "ConsoleController.h"

//namespaces

using namespace std;

//enums

enum Scenes {
	SCENE_MAIN,
	SCENE_GAME
};


//structs

struct SimpleTriangle {
	glm::vec3 firstPoint;
	glm::vec3 secondPoint;
	glm::vec3 thirdPoint;

	inline SimpleTriangle() {

	}

	inline SimpleTriangle(glm::vec3 x, glm::vec3 y, glm::vec3 z) {
		this->firstPoint = x;
		this->secondPoint = y;
		this->thirdPoint = z;
	}
};


struct SimpleLine {
	glm::vec3 firstPoint;
	glm::vec3 secondPoint;

	inline SimpleLine() {

	}

	inline SimpleLine(glm::vec3 x, glm::vec3 y) {
		this->firstPoint = x;
		this->secondPoint = y;
	}
};

struct SimpleFan {
	glm::vec3 firstPoint;
	vector<glm::vec3> points;

	inline SimpleFan() {

	}

	inline SimpleFan(glm::vec3 firstp, vector<glm::vec3> _points) {
		this->firstPoint = firstp;
		this->points = _points;
	}
};

struct MESH
{
	GLuint VAO;
	unsigned int IndicesCount;
};

struct BasicCard
{

	GLuint VAO;
	GLuint Shader;
	GLuint Texture;

	glm::vec3 Pos;
	glm::vec3 Scale;
	glm::vec3 Rotation;

	glm::mat4 ModelMatrix;
	glm::mat4 VPMatrix;
	unsigned IndicesCount;

	inline BasicCard() {

	}

	inline BasicCard(glm::vec3 _Pos, glm::vec3 _Scale, glm::vec3 _Rotation, std::shared_ptr<MESH> _mesh, GLuint _Shader, GLuint _Texture)
	{
		this->VAO = _mesh->VAO;
		this->Pos = _Pos;
		this->Scale = _Scale;
		this->Rotation = _Rotation;
		this->IndicesCount = _mesh->IndicesCount;
		this->Shader = _Shader;
		this->Texture = _Texture;
	}
	

	
};

namespace Utility
{
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;
	const std::string ObjectShaderVert = "Resources/Shaders/ObjectShaderV.vs";
	const std::string ObjectShaderFrag = "Resources/Shaders/ObjectShaderF.fs";
	const std::string BasicShaderVert = "Resources/Shaders/BasicShader.vs";
	const std::string BasicShaderFrag = "Resources/Shaders/BasicShader.vs";
	const std::string DesertTexture = "Resources/Textures/desert.jpg";
	const std::string NormalFontString = "Resources/Fonts/arial.ttf";
	const std::string TextShaderVert = "Resources/Shaders/Text.vs";
	const std::string TextShaderFrag = "Resources/Shaders/Text.fs";
}

#include "MeshManager.h"