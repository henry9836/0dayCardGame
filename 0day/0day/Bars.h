#pragma once
#include "GameObject.h"
#include "Character.h"
#include "TextManager.h"
#include "Util.h"

class BarsRender : public RenderObject
{
public:
	BarsRender(std::shared_ptr<MESH> _mesh, GLuint _texture, Game* _game, GLuint _shaderProgram, Character * _Characterptr, bool _isHealthBar);
	~BarsRender();
	void Render(Transform* _transform);

	void ChangingVertices(float _Value);

	
private:
	GLuint VBO;
	vector<GLfloat> Vertices;
	bool isHealthBar;
	Character* characterPtr;
	CTextLabel* barInfo;
};

