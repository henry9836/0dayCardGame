#pragma once

//header files
#include <glew.h>
#include <freeglut.h>
#include <vector>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>
#include <iostream>

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
};
