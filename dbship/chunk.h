#pragma once

#include <iostream>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Chunk
{
public:
	Chunk();
	~Chunk();
	glm::vec3 ChunkSize();
};

