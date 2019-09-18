#include "MeshManager.h"

std::shared_ptr<MESH> MeshManager::SquareMesh = nullptr;
std::shared_ptr<MESH> MeshManager::ChangingSquareMesh = nullptr;

std::shared_ptr<MeshManager> MeshManager::MeshManagerptr = nullptr;

GLuint MeshManager::BasicShader;

GLuint MeshManager::Texture;
std::shared_ptr<MESH> MeshManager::GetMesh(Object_Attributes _ObjectType)
{
	if (_ObjectType == CARD_ENTITY) return SquareMesh;

	if (_ObjectType == BAR_ENTITY) return ChangingSquareMesh;

	return nullptr;
}

MeshManager::MeshManager()
{
	GLuint VAO, VBO, EBO;

	BasicShader = ShaderLoader::CreateProgram(Utility::BasicShaderVert.data(), Utility::BasicShaderFrag.data());
	//Defines Square Vertices
	std::vector<GLfloat> SquareVerts = {
		// Positions        // Normal Coords   // TexCoords	
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,  0.0f, 0.0f,	// Top - Left
		 -1.0f, -1.0f, 0.0f,	1.0f, 0.0f, 0.0f,  0.0f, 1.0f,	// Bot - Left
		 1.0f, -1.0f, 0.0f,	    1.0f, 1.0f, 0.0f,  1.0f, 1.0f,	// Bot - Right
		 1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,  1.0f, 0.0f	// Top - Right
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
	glBufferData(GL_ARRAY_BUFFER, SquareVerts.size() * sizeof(GLfloat), &SquareVerts[0], GL_STATIC_DRAW);

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
	SquareMesh->VBO = VBO;
	SquareMesh->IndicesCount = sizeof(SquareIndices);
	SquareMesh->Vertices = SquareVerts;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Binding and Setting the buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, SquareVerts.size() * sizeof(GLfloat), &SquareVerts[0], GL_DYNAMIC_DRAW);

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

	ChangingSquareMesh = make_shared<MESH>();
	ChangingSquareMesh->VAO = VAO;
	ChangingSquareMesh->VBO = VBO;
	ChangingSquareMesh->Vertices = SquareVerts;
	ChangingSquareMesh->IndicesCount = sizeof(SquareIndices);
}


MeshManager::~MeshManager()
{
	SquareMesh = nullptr;
	ChangingSquareMesh = nullptr;
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
		return BasicShader;
	}
}

GLuint MeshManager::SetTexture(const char* _TextureFilename)
{
	GLuint Texture;
	int width, height;

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	//Setting Texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Setting texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Getting the image from filepath
	unsigned char* image = SOIL_load_image(
		_TextureFilename,
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA
	);

	//Generating the texture from image data
	if (image)
	{
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
	}
	else
	{
		Console_OutputLog(L"Failed to load Texture", LOGWARN);
	}
	//Freeing up data
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return Texture;
}