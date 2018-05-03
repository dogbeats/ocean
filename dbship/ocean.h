#pragma once
#include "chunk.h"

#include <vector>

class Ocean :
	public Chunk
{
public:
	Ocean();
	~Ocean();
	glm::vec3 ReturnDimensions();
	std::vector<float> CreateVertices();
	std::vector<unsigned int> CreateIndices();
	std::vector<float> UpdateVertices(float total_time, float height);
	int GetStartOfMidpoints();
	void SetWaveForce(float force);
	float GetWaveForce();

private:
	std::vector<float> vertices_flex;
	std::vector<unsigned int>indices_flex;
	const int max_detail = 12;
	const int sides = 4;
	int wave_points = 0, start_of_midpoints = 0;
	float wave_force;
	glm::vec3 GetDistance();
};

