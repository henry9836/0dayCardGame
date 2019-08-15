#include "MeshManager.h"

std::shared_ptr<MESH> MeshManager::SquareMesh = nullptr;

std::shared_ptr<MeshManager> MeshManager::MeshManagerptr = nullptr;

GLuint MeshManager::BasicShader;

GLuint MeshManager::Texture;
std::shared_ptr<MESH> MeshManager::GetMesh(Object_Attributes _ObjectType)
{
	if (_ObjectType == CARD_ENTITY) return SquareMesh;

	return nullptr;
}

MeshManager::MeshManager()
{
	GLuint VAO, VBO, EBO;

	BasicShader = ShaderLoader::CreateProgram(Utility::ObjectShaderVert.data(), Utility::ObjectShaderFrag.data());

	//Defines Square Vertices
	GLfloat SquareVerts[] =
	{
		// Positions             // Normal Coords        // TexCoords
		// Front Face
		-1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f,      0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,        0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,       0.0f, 0.0f, 1.0f,      1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,      0.0f, 0.0f, 1.0f,      0.0f, 1.0f,
	};
	//Defines Square Indices
	GLuint SquareIndices[] =
	{
		0,1,2,
		0,2,3,
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Binding and Setting the buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareVerts), SquareVerts, GL_STATIC_DRAW);

	//Enabling the Postitional floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Enabling Normal Floats
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Enabling the Texture floats
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SquareIndices), SquareIndices, GL_STATIC_DRAW);

	//Freeing up data
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	SquareMesh = make_shared<MESH>();
	SquareMesh->VAO = VAO;
	SquareMesh->IndicesCount = sizeof(SquareIndices);
}


MeshManager::~MeshManager()
{
	SquareMesh = nullptr;
}

std::shared_ptr<MeshManager> MeshManager::GetInstance()
{
	if (MeshManagerptr == nullptr)
	{
		MeshManagerptr = std::shared_ptr<MeshManager>(new MeshManager());
	}
	return MeshManagerptr;
}

void MeshManager::DestoryInstance()
{
	MeshManagerptr = nullptr;
}

GLuint MeshManager::GetShaderProgram(Shader_Attributes _ShaderType)
{
	if (_ShaderType == BASIC_SHADER)
	{
		return BasicShader;
	}
	else
	{
		Console_OutputLog(L"Shader Failed To Load", LOGWARN);
	}
}

GLuint MeshManager::SetTexture(const char* _Texture)
{
	GLuint Texture;
	int width, height;

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	//Getting the image from filepath
	unsigned char* image = SOIL_load_image(
		_Texture,
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA
	);

	//Generating the texture from image data
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width, height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image
	);

	//Generating mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Setting Texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Setting texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Freeing up data
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return Texture;
}