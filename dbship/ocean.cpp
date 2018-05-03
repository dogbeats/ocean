#include "ocean.h"



Ocean::Ocean()
{
}


Ocean::~Ocean()
{
}

std::vector<unsigned int> Ocean::CreateIndices()
{
	int indices_count = (this->wave_points*sides);

	if (sides == 4)
	{
		float point = indices_count - 5;

		for (int i = 0; i < point; i++)
		{
			this->indices_flex.push_back(i * 2);
			this->indices_flex.push_back(i * 2 + 1);
			this->indices_flex.push_back(i * 2 + 3);
			this->indices_flex.push_back(i * 2);
			this->indices_flex.push_back(i * 2 + 3);
			this->indices_flex.push_back(i * 2 + 2);
		}

		this->indices_flex.push_back((point) * 2);
		this->indices_flex.push_back((point) * 2 + 1);
		this->indices_flex.push_back(1);
		this->indices_flex.push_back((point) * 2);
		this->indices_flex.push_back(1);
		this->indices_flex.push_back(0);

		//top of wave
		int rows = this->wave_points - 1;
		int length_t = this->wave_points - 1; //to replace

										//first row
		for (int i = 0; i < length_t; i++)
		{
			this->indices_flex.push_back(i * 2);
			this->indices_flex.push_back(i * 2 + 2);
			if (i == length_t - 1 && i != 0)
				this->indices_flex.push_back(this->wave_points * 2);
			else
				this->indices_flex.push_back(this->start_of_midpoints + i);

			this->indices_flex.push_back(i * 2);
			if (i == 0)
				this->indices_flex.push_back(this->start_of_midpoints - 4);
			else
				this->indices_flex.push_back(this->start_of_midpoints + i - 1);
			if (i == length_t - 1 && i != 0)
				this->indices_flex.push_back(this->wave_points * 2);
			else
				this->indices_flex.push_back(this->start_of_midpoints + i);
		}

		//mid rows
		if (rows > 2)
		{
			for (int j = 1; j <= rows - 2; j++) //rows - 1
			{
				for (int i = 0; i < length_t; i++)
				{
					if (i == 0)
					{
						this->indices_flex.push_back((this->wave_points - 1) * 8 - j * 2);
						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2));
						this->indices_flex.push_back(this->start_of_midpoints + (j)*(this->wave_points - 2));

						this->indices_flex.push_back((this->wave_points - 1) * 8 - j * 2);
						this->indices_flex.push_back(this->start_of_midpoints + (j)*(this->wave_points - 2));
						this->indices_flex.push_back((this->wave_points - 1) * 8 - j * 2 - 2);
					}
					else if (i == length_t - 1 && i != 0)
					{
						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2) + i - 1);
						this->indices_flex.push_back((this->wave_points - 1) * 2 + j * 2);
						this->indices_flex.push_back((this->wave_points - 1) * 2 + j * 2 + 2);

						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2) + i - 1);
						this->indices_flex.push_back((this->wave_points - 1) * 2 + j * 2 + 2);
						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2) + i + (this->wave_points - 3));
					}
					else
					{
						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2) + i - 1);
						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2) + i);
						this->indices_flex.push_back(this->start_of_midpoints + (j)*(this->wave_points - 2) + i);

						this->indices_flex.push_back(this->start_of_midpoints + (j - 1)*(this->wave_points - 2) + i - 1);
						this->indices_flex.push_back(this->start_of_midpoints + (j)*(this->wave_points - 2) + i);
						this->indices_flex.push_back(this->start_of_midpoints + (j)*(this->wave_points - 2) + i - 1);
					}
				}
			}
		}

		//bottom row
		for (int i = 0; i < length_t; i++)
		{
			if (i == 0)
			{
				this->indices_flex.push_back((this->wave_points - 1) * 6 + 2);
				this->indices_flex.push_back(this->start_of_midpoints + (this->wave_points + (this->wave_points - 2)*(this->wave_points - 4)) - 2);
				this->indices_flex.push_back((this->wave_points - 1) * 6 - 2);

				this->indices_flex.push_back((this->wave_points - 1) * 6 + 2);
				this->indices_flex.push_back((this->wave_points - 1) * 6 - 2);
				this->indices_flex.push_back((this->wave_points - 1) * 6);
			}
			else if (i == length_t - 1 && i != 0)
			{
				this->indices_flex.push_back(this->start_of_midpoints + (this->wave_points + (this->wave_points - 2)*(this->wave_points - 4)) - (3 - i));
				this->indices_flex.push_back((this->wave_points - 1) * 4 - 2);
				this->indices_flex.push_back((this->wave_points - 1) * 4);

				this->indices_flex.push_back(this->start_of_midpoints + (this->wave_points + (this->wave_points - 2)*(this->wave_points - 4)) - (3 - i));
				this->indices_flex.push_back((this->wave_points - 1) * 4);
				this->indices_flex.push_back((this->wave_points - 1) * 4 + 2);
			}
			else
			{
				this->indices_flex.push_back(this->start_of_midpoints + (this->wave_points + (this->wave_points - 2)*(this->wave_points - 4)) - (3 - i));
				this->indices_flex.push_back(this->start_of_midpoints + (this->wave_points + (this->wave_points - 2)*(this->wave_points - 4)) - (2 - i));
				this->indices_flex.push_back((this->wave_points - 1) * 6 - 2 * (1 + i));

				this->indices_flex.push_back(this->start_of_midpoints + (this->wave_points + (this->wave_points - 2)*(this->wave_points - 4)) - (3 - i));
				this->indices_flex.push_back((this->wave_points - 1) * 6 - 2 * (1 + i));
				this->indices_flex.push_back((this->wave_points - 1) * 6 - 2 * (1 + i) + 2);
			}
		}
	}
	else
	{
		for (int i = 0; i < indices_count; i++)
		{
			this->indices_flex.push_back(i * 2);
			this->indices_flex.push_back(i * 2 + 1);
			this->indices_flex.push_back(i * 2 + 3);
			this->indices_flex.push_back(i * 2);
			this->indices_flex.push_back(i * 2 + 3);
			this->indices_flex.push_back(i * 2 + 2);
		}
	}

	return this->indices_flex;
}

std::vector<float> Ocean::CreateVertices()
{
	glm::vec3 dimensions = this->ReturnDimensions();
	//float width[] = {-dimensions[0],dimensions[0]}, height[] = { -dimensions[1],dimensions[1] }, depth[] = { -dimensions[2],dimensions[2] };
	float width[] = { -1.5f,1.5f }, height[] = { -0.5f,0.5f }, depth[] = { -1.5f,1.5f };
	this->wave_points = this->max_detail;
	int mid_points = (this->wave_points - 2);
	float wave_height = 0.8f;

	for (int j = 0; j < this->wave_points; j++)
	{
		//top tri
		this->vertices_flex.push_back(width[0] + (j*(width[1] * 2 / (this->wave_points - 1)))); //x
		this->vertices_flex.push_back(height[1]); //y
		this->vertices_flex.push_back(depth[0]); //z
		this->vertices_flex.push_back(1.0f); //r
		this->vertices_flex.push_back(0.0f); //g
		this->vertices_flex.push_back(0.0f); //b

		 //bottom tri
		this->vertices_flex.push_back(width[0] + (j*(width[1] * 2 / (this->wave_points - 1)))); //x
		this->vertices_flex.push_back(height[0]); //y
		this->vertices_flex.push_back(depth[0]); //z
		this->vertices_flex.push_back(0.0f); //r
		this->vertices_flex.push_back(1.0f); //g
		this->vertices_flex.push_back(0.0f); //b	
	}

	if (sides >= 2)
	{
		for (int j = 1; j < this->wave_points; j++)
		{
			this->vertices_flex.push_back(width[1]); //x
			this->vertices_flex.push_back(height[1]); //y
			this->vertices_flex.push_back(depth[0] + (j*(depth[1] * 2 / (this->wave_points - 1)))); //z
			this->vertices_flex.push_back(1.0f); //r
			this->vertices_flex.push_back(0.0f); //g
			this->vertices_flex.push_back(0.0f); //b

			this->vertices_flex.push_back(width[1]); //x
			this->vertices_flex.push_back(height[0]); //y
			this->vertices_flex.push_back(depth[0] + (j*(depth[1] * 2 / (this->wave_points - 1)))); //z
			this->vertices_flex.push_back(0.0f); //r
			this->vertices_flex.push_back(1.0f); //g
			this->vertices_flex.push_back(0.0f); //b	
		}
	}

	if (sides >= 3)
	{
		for (int j = this->wave_points - 1; j > 0; j--)
		{
			this->vertices_flex.push_back(width[1] - (this->wave_points - j)*(width[1] * 2 / (this->wave_points - 1))); //x //-((1-j)*(width[1] / (this->wave_points - 1)))
			this->vertices_flex.push_back(height[1]); //y
			this->vertices_flex.push_back(depth[1]); //z
			this->vertices_flex.push_back(1.0f); //r
			this->vertices_flex.push_back(0.0f); //g
			this->vertices_flex.push_back(0.0f); //b

			this->vertices_flex.push_back(width[1] - (this->wave_points - j)*(width[1] * 2 / (this->wave_points - 1))); //x
			this->vertices_flex.push_back(height[0]); //y
			this->vertices_flex.push_back(depth[1]); //z
			this->vertices_flex.push_back(0.0f); //r
			this->vertices_flex.push_back(1.0f); //g
			this->vertices_flex.push_back(0.0f); //b	
		}
	}

	if (sides >= 4)
	{
		for (int j = this->wave_points - 1; j > 0; j--)
		{
			this->vertices_flex.push_back(width[0]); //x
			this->vertices_flex.push_back(height[1]); //y
			this->vertices_flex.push_back(depth[1] - ((this->wave_points - j)*(depth[1] * 2 / (this->wave_points - 1)))); //z
			this->vertices_flex.push_back(1.0f); //r
			this->vertices_flex.push_back(0.0f); //g
			this->vertices_flex.push_back(0.0f); //b

			this->vertices_flex.push_back(width[0]); //x
			this->vertices_flex.push_back(height[0]); //y
			this->vertices_flex.push_back(depth[1] - ((this->wave_points - j)*(depth[1] * 2 / (this->wave_points - 1)))); //z
			this->vertices_flex.push_back(0.0f); //r
			this->vertices_flex.push_back(1.0f); //g
			this->vertices_flex.push_back(0.0f); //b	
		}

		this->start_of_midpoints = this->vertices_flex.size() / 6;

		for (int j = 0; j < mid_points; j++) //depth
		{
			for (int i = 0; i < mid_points; i++) //width
			{
				this->vertices_flex.push_back(width[0] + ((i + 1)*(width[1] * 2 / (this->wave_points - 1)))); //x
				this->vertices_flex.push_back(height[1]); //y
				this->vertices_flex.push_back(depth[0] + ((j + 1)*(depth[1] * 2 / (this->wave_points - 1)))); //z
				this->vertices_flex.push_back(0.0f); //r
				this->vertices_flex.push_back(0.0f); //g
				this->vertices_flex.push_back(1.0f); //b
			}
		}
	}

	return this->vertices_flex;
}

std::vector<float> Ocean::UpdateVertices(float total_time, float height)
{
	if (this->wave_force != 0)
	{
		for (int i = 0; i < this->start_of_midpoints; i++) //set i < vertices_flex.size()/6 for top layer only
			this->vertices_flex[i * 12 + 1] = height + (glm::sin(total_time + 0.0f - this->vertices_flex[i * 12]) / this->wave_force);

		for (int i = this->start_of_midpoints; i < this->vertices_flex.size() / 6; i++)
		{
			this->vertices_flex[i * 6 + 1] = height + (glm::sin((total_time)+(i / 55 + 1)*glm::distance(glm::vec3(7.0f, 0.0f, -8.0f), glm::vec3(this->vertices_flex[i * 6], 0.0f, this->vertices_flex[i * 6 + 2]))) / this->wave_force); //(0.0f - vertices_flex[i * 6]) + (0.0f - vertices_flex[i * 6 + 2])
		}
	}

	return this->vertices_flex;
}

int Ocean::GetStartOfMidpoints()
{
	return this->start_of_midpoints;
}

void Ocean::SetWaveForce(float force)
{
	this->wave_force = force;
}

float Ocean::GetWaveForce()
{
	return this->wave_force;
}

glm::vec3 Ocean::GetDistance()
{
	return glm::vec3{ 0.0f,0.0f,0.0f };
}

glm::vec3 Ocean::ReturnDimensions()
{
	return this->ChunkSize();
}
