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
	ENEMY_ENTITY,
	NONE,
};

enum Shader_Attributes
{
	BASIC_SHADER
};

struct MESH
{
	GLuint VAO;
	unsigned int IndicesCount;
};

class MeshManager
{
public:
	~MeshManager();
	static std::shared_ptr<MeshManager> GetInstance();
	static void DestoryInstance();

	static std::shared_ptr<MESH> GetMesh(Object_Attributes _ObjectType);

	GLuint GetShaderProgram(Shader_Attributes _ShaderType);

	GLuint SetTexture(const char* _Texture);

private:
	MeshManager();

	static std::shared_ptr<MeshManager> MeshManagerptr;

	static GLuint BasicShader;

	// Mesh ptrs
	static std::shared_ptr<MESH> SquareMesh;
};

