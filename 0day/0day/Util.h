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
	const std::string ZERODAY = "Resources/Textures/CARDS/0day.png";
	const std::string account = "Resources/Textures/CARDS/account.png";
	const std::string circle = "Resources/Textures/CARDS/circle.png";
	const std::string dos = "Resources/Textures/CARDS/dos.png";
	const std::string enhnaced = "Resources/Textures/CARDS/enhanced.png";
	const std::string enterkey = "Resources/Textures/CARDS/enterkey.png";
	const std::string enumeration = "Resources/Textures/CARDS/enumeration.png";
	const std::string falseified = "Resources/Textures/CARDS/false.png";
	const std::string FB = "Resources/Textures/CARDS/FB.png";
	const std::string firewall = "Resources/Textures/CARDS/firewall.png";
	const std::string fuzzer = "Resources/Textures/CARDS/fuzzer.png";
	const std::string login = "Resources/Textures/CARDS/login.png";
	const std::string robofight = "Resources/Textures/CARDS/robofight.png";
	const std::string selfmod = "Resources/Textures/CARDS/selfmod.png";
	const std::string skull = "Resources/Textures/CARDS/skull.png";
	const std::string SQL = "Resources/Textures/CARDS/SQL.png";
	const std::string stager = "Resources/Textures/CARDS/stager.png";
	const std::string sunglasses = "Resources/Textures/CARDS/sunglasses.png";
	const std::string systemreset = "Resources/Textures/CARDS/systemreset.png";
	const std::string tape = "Resources/Textures/CARDS/tape.png";

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