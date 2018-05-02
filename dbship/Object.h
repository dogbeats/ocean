#pragma once
#include "Shader.h"

class Object
{
public:
	Object();
	~Object();
	void Render(float vertices[]);
	unsigned int GetVAO();
	
private:
	unsigned int VBO, VAO;

};

