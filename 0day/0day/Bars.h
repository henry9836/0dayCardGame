#pragma once
#include "GameObject.h"

class Bars : public GameObject
{
public:
	void Tick(float deltaTime) {};
	void Render() { _r->Render(&transform); };

	void SetTexture(GLuint _tex) { _r->SetTexture(_tex); };
	void SetShader(GLuint _shader) { _r->SetTexture(_shader); };
private:
	
};