#pragma once

#include <fstream>
#include <glew.h>
#include <glm.hpp>
#include <glut.h>
#include <SOIL.h>
#include "ShaderLoader.h"
#include "Util.h"
#include "ConsoleController.h"

enum Object_Attributes
{
	CARD_ENTITY,
	BAR_ENTITY,
	ENEMY_ENTITY,
	NONE,
};

enum Shader_Attributes
{
	BASIC_SHADER
};

class MeshManager
{
public:
	~MeshManager();
	static std::shared_ptr<MeshManager> GetInstance();
	static void DestoryInstance();

	static std::shared_ptr<MESH> GetMesh(Object_Attributes _ObjectType);

	static GLuint GetShaderProgram(Shader_Attributes _ShaderType);

	static GLuint SetTexture(const char* _Texture);

private:
	MeshManager();

	static std::shared_ptr<MeshManager> MeshManagerptr;

	static GLuint BasicShader;

	static GLuint Texture;

	// Mesh ptrs
	static std::shared_ptr<MESH> SquareMesh;
	static std::shared_ptr<MESH> ChangingSquareMesh;
};

