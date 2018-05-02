#pragma once

#include <iostream>
#include <vector>

// GLAD
#include <glad/glad.h> 

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class MainGame
{
public:
	MainGame();
	~MainGame();
	int Run();

};

