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
	SCENE_SELECTION,
	SCENE_GAME,
	SCENE_HOWTOPLAY,
	SCENE_LOSE
};


struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	inline Transform() {

	}
	inline Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scal) {
		position = pos;
		rotation = rot;
		scale = scal;
	}
};

//structs

struct SimpleTriangle {
	glm::vec3 firstPoint;
	glm::vec3 secondPoint;
	glm::vec3 thirdPoint;

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
	GLuint VAO, VBO;
	std::vector<GLfloat> Vertices;
	unsigned int IndicesCount;
};

namespace Utility
{
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;
	const std::string ObjectShaderVert = "Resources/Shaders/ObjectShaderV.vs";
	const std::string ObjectShaderFrag = "Resources/Shaders/ObjectShaderF.fs";
	const std::string BasicShaderVert = "Resources/Shaders/BasicShader.vs";
	const std::string BasicShaderFrag = "Resources/Shaders/BasicShader.fs";
	const std::string DesertTexture = "Resources/Textures/test.png";
	const std::string NormalFontString = "Resources/Fonts/TerminusTTF-4.47.0.ttf";
	const std::string TextShaderVert = "Resources/Shaders/Text.vs";
	const std::string TextShaderFrag = "Resources/Shaders/Text.fs";
}

namespace Textures
{
	const std::string RedRing = "Resources/Textures/REDRINGCard.png";
	const std::string DDOS = "Resources/Textures/DDOSCard.png";
	const std::string SQL = "Resources/Textures/SQLCard.png";

	const std::string AccountTransfer = "Resources/Textures/accounttransfer.png";
	const std::string EnterKey = "Resources/Textures/enterkey.png";
	const std::string Enumeration = "Resources/Textures/enumeration.png";
	const std::string FalsifiedCredentials = "Resources/Textures/FalsifiedCredentials.png";
	const std::string ForkBomb = "Resources/Textures/forkbomb.png";
	const std::string ModCode = "Resources/Textures/Self-Modifiying Code.png";
	const std::string Skull = "Resources/Textures/skullonscreen.png";


	const std::string Player1Indicator = "Resources/Textures/Player1Indicator.png";
	const std::string Player2Indicator = "Resources/Textures/Player2Indicator.png";
}

namespace Shaders
{

}

namespace Fonts
{

}
#include "MeshManager.h"