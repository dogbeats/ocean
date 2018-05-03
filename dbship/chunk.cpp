#include "chunk.h"


Chunk::Chunk()
{
}


Chunk::~Chunk()
{
}

glm::vec3 Chunk::ChunkSize()
{
	return { 1.5f,0.5f,1.5f };
}