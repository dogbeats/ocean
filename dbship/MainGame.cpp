#include "MainGame.h"
#include "Object.h"
#include "Shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Object object;
float delta_time = 0, current_frame = 0, previous_frame = 0, total_time;

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void ProcessInput(GLFWwindow *window)
{

}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{

}

int MainGame::Run()
{
	float vertices[] = {
		//front
		// positions         // colors
		//0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//top right
		//0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,  // bottom right
		//-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,  // bottom left
		//-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,   // top left

		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,   // top left
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,  // bottom left
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//top right
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,  // bottom right

		//top
		// positions         // colors
		//0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f,	//top right
		//0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 0.0f,  // bottom right
		//-0.5f, 0.5f, 1.0f,		0.0f, 1.0f, 0.0f,  // bottom left
		//-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 1.0f   // top left
	};

	std::vector<float> vertices_flex;
	std::vector<unsigned int>indices_flex;
	float width[] = { -1.5f, 1.5f };
	float height[] = { -0.5f, 0.5f };
	float depth[] = { -1.5f, 1.5f };
	int wave_points = 32;
	int sides = 4;
	int mid_points = (wave_points - 2);
	int start_of_midpoints = 0;
	//const bool is_3d = true;
	int indices_count = (wave_points*sides);
	float wave_force = 7; //lower = harsher waves, higher = smoother waves
	float wave_height = 0.8f;

	float test_coord = 0.0f;

	//top
	for (int j = 0; j < wave_points; j++)
	{
		vertices_flex.push_back(width[0] + (j*(width[1] * 2 / (wave_points - 1)))); //x
		vertices_flex.push_back(height[1]); //y
		vertices_flex.push_back(depth[0]); //z
		//vertices_flex.push_back(depth[0] + (j*(depth[1] * 2 / (wave_points - 1)))); //z
		
		vertices_flex.push_back(1.0f); //r
		vertices_flex.push_back(0.0f); //g
		vertices_flex.push_back(0.0f); //b

		//bottom
		vertices_flex.push_back(width[0] + (j*(width[1] * 2 / (wave_points - 1)))); //x
		vertices_flex.push_back(height[0]); //y
		vertices_flex.push_back(depth[0]); //z
		//vertices_flex.push_back(depth[0] + (j*(depth[1] * 2 / (wave_points - 1)))); //z

		vertices_flex.push_back(0.0f); //r
		vertices_flex.push_back(1.0f); //g
		vertices_flex.push_back(0.0f); //b	
	}

	if (sides >= 2)
	{
		for (int j = 1; j < wave_points; j++)
		{
			vertices_flex.push_back(width[1]); //x
			vertices_flex.push_back(height[1]); //y
			vertices_flex.push_back(depth[0] + (j*(depth[1] * 2 / (wave_points - 1)))); //z

			vertices_flex.push_back(1.0f); //r
			vertices_flex.push_back(0.0f); //g
			vertices_flex.push_back(0.0f); //b

										   //bottom
			vertices_flex.push_back(width[1]); //x
			vertices_flex.push_back(height[0]); //y
			vertices_flex.push_back(depth[0] + (j*(depth[1] * 2 / (wave_points - 1)))); //z

			vertices_flex.push_back(0.0f); //r
			vertices_flex.push_back(1.0f); //g
			vertices_flex.push_back(0.0f); //b	
		}
	}

	if (sides >= 3)
	{
		for (int j = wave_points-1; j > 0; j--)
		{
			vertices_flex.push_back(width[1] - (wave_points - j)*(width[1] * 2 / (wave_points-1))); //x //-((1-j)*(width[1] / (wave_points - 1)))
			vertices_flex.push_back(height[1]); //y
			vertices_flex.push_back(depth[1]); //z

			vertices_flex.push_back(1.0f); //r
			vertices_flex.push_back(0.0f); //g
			vertices_flex.push_back(0.0f); //b

			//bottom
			vertices_flex.push_back(width[1] - (wave_points - j)*(width[1] * 2 / (wave_points - 1))); //x
			vertices_flex.push_back(height[0]); //y
			vertices_flex.push_back(depth[1]); //z

			vertices_flex.push_back(0.0f); //r
			vertices_flex.push_back(1.0f); //g
			vertices_flex.push_back(0.0f); //b	
		}
	}

	if (sides >= 4)
	{
		for (int j = wave_points - 1; j > 0; j--)
		{
			vertices_flex.push_back(width[0]); //x
			vertices_flex.push_back(height[1]); //y
			vertices_flex.push_back(depth[1] - ((wave_points-j)*(depth[1] * 2 / (wave_points - 1)))); //z

			vertices_flex.push_back(1.0f); //r
			vertices_flex.push_back(0.0f); //g
			vertices_flex.push_back(0.0f); //b

										   //bottom
			vertices_flex.push_back(width[0]); //x
			vertices_flex.push_back(height[0]); //y
			vertices_flex.push_back(depth[1] - ((wave_points - j)*(depth[1] * 2 / (wave_points - 1)))); //z

			vertices_flex.push_back(0.0f); //r
			vertices_flex.push_back(1.0f); //g
			vertices_flex.push_back(0.0f); //b	
		}

		start_of_midpoints = vertices_flex.size() / 6;
		//std::cout << "Start of midpoints: " << start_of_midpoints << "\n";
		for (int j = 0; j < mid_points; j++) //depth
		{
			for (int i = 0; i < mid_points; i++) //width
			{
				vertices_flex.push_back(width[0] + ((i + 1)*(width[1] * 2 / (wave_points - 1)))); //x
				vertices_flex.push_back(height[1]); //y
				vertices_flex.push_back(depth[0] + ((j + 1)*(depth[1] * 2 / (wave_points - 1)))); //z
				
				vertices_flex.push_back(0.0f); //r
				vertices_flex.push_back(0.0f); //g
				vertices_flex.push_back(1.0f); //b
				
				//std::cout << "Midpoints - x: " << width[0] + ((i+1)*(width[1] * 2 / (wave_points - 1))) << "   y: " << height[1] << "   z: " << depth[0] + ((j+1)*(depth[1] * 2 / (wave_points - 1))) << "\n";

				//std::cout << "Midpoints - x: " << width[0] + (width[1] * 2 / (i+2)) << "   y: " << height[1] << "   z: " << depth[0] + (depth[1] * 2 / (j+2)) << "\n";
			}
		}
	}
	//std::cout << "New Size: " << vertices_flex.size() / 6 << "\n";
	if (sides == 4)
	{
		float point = indices_count - 5;

		for (int i = 0; i < point; i++)
		{
			indices_flex.push_back(i * 2);
			indices_flex.push_back(i * 2 + 1);
			indices_flex.push_back(i * 2 + 3);
			indices_flex.push_back(i * 2);
			indices_flex.push_back(i * 2 + 3);
			indices_flex.push_back(i * 2 + 2);
		}
		
		indices_flex.push_back((point) * 2);
		indices_flex.push_back((point) * 2 + 1);
		indices_flex.push_back(1);
		indices_flex.push_back((point) * 2);
		indices_flex.push_back(1);
		indices_flex.push_back(0);

		//top of wave
		int rows = wave_points - 1;

		int length_t = wave_points - 1; //to replace

		//first row
		for (int i = 0; i < length_t; i++)
		{
			indices_flex.push_back(i * 2);
			indices_flex.push_back(i * 2 + 2);
			if (i == length_t-1 && i != 0)
				indices_flex.push_back(wave_points * 2);
			else
				indices_flex.push_back(start_of_midpoints + i);

			//std::cout << "start_of_midpoints + i + 1  " << start_of_midpoints + i + 1 << "\n";

			indices_flex.push_back(i * 2);
			if (i == 0)
				indices_flex.push_back(start_of_midpoints - 4);
			else
				indices_flex.push_back(start_of_midpoints + i - 1);
			if(i == length_t - 1 && i != 0)
				indices_flex.push_back(wave_points * 2);
			else
				indices_flex.push_back(start_of_midpoints + i);
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
						indices_flex.push_back((wave_points - 1) * 8 - j*2);
						indices_flex.push_back(start_of_midpoints + (j-1)*(wave_points - 2));
						indices_flex.push_back(start_of_midpoints + (j)*(wave_points - 2));

						indices_flex.push_back((wave_points - 1) * 8 - j * 2);
						indices_flex.push_back(start_of_midpoints + (j)*(wave_points - 2));
						indices_flex.push_back((wave_points - 1) * 8 - j * 2 - 2);

						//indices_flex.push_back(28); //30,34,37
						//indices_flex.push_back(37);
						//indices_flex.push_back(40);
					}
					else if (i == length_t - 1 && i != 0)
					{
						indices_flex.push_back(start_of_midpoints + (j - 1)*(wave_points - 2) + i-1);
						indices_flex.push_back((wave_points - 1) * 2 + j * 2);
						indices_flex.push_back((wave_points - 1) * 2 + j * 2 + 2);

						indices_flex.push_back(start_of_midpoints + (j - 1)*(wave_points - 2) + i - 1);
						indices_flex.push_back((wave_points - 1) * 2 + j * 2 + 2);
						indices_flex.push_back(start_of_midpoints + (j - 1)*(wave_points - 2) + i + (wave_points-3));

						//indices_flex.push_back(36); //39,12,14
						//indices_flex.push_back(10);
						//indices_flex.push_back(12);
					}
					else
					{
						indices_flex.push_back(start_of_midpoints + (j - 1)*(wave_points - 2) + i - 1);
						indices_flex.push_back(start_of_midpoints + (j - 1)*(wave_points - 2) + i);
						indices_flex.push_back(start_of_midpoints + (j)*(wave_points - 2) + i);

						indices_flex.push_back(start_of_midpoints + (j - 1)*(wave_points - 2) + i - 1);
						indices_flex.push_back(start_of_midpoints + (j)*(wave_points - 2) + i);
						indices_flex.push_back(start_of_midpoints + (j)*(wave_points - 2) + i - 1);
					}
				}
			}
		}

		//bottom row
		for (int i = 0; i < length_t; i++)
		{
			if (i == 0)
			{
				indices_flex.push_back((wave_points - 1) * 6 + 2);
				indices_flex.push_back(start_of_midpoints + (wave_points+(wave_points-2)*(wave_points-4)) - 2);
				indices_flex.push_back((wave_points - 1) * 6 - 2);

				indices_flex.push_back((wave_points - 1) * 6 + 2);
				indices_flex.push_back((wave_points - 1) * 6 - 2);
				indices_flex.push_back((wave_points - 1) * 6);
			}
			else if (i == length_t - 1 && i != 0)
			{
				//indices_flex.push_back(vertices_flex.size() / 6 - 1);
				//indices_flex.push_back(start_of_midpoints - 12);(4 * (length_t-2)
				//indices_flex.push_back(vertices_flex.size() / 6 - 1);
				//indices_flex.push_back((wave_points * 4 - 6));
				//indices_flex.push_back((wave_points - 1) * 6 - ((i + 1) * 2));

				indices_flex.push_back(start_of_midpoints + (wave_points + (wave_points - 2)*(wave_points - 4)) - (3 - i));
				indices_flex.push_back((wave_points - 1) * 4 - 2);
				indices_flex.push_back((wave_points - 1) * 4);

				indices_flex.push_back(start_of_midpoints + (wave_points + (wave_points - 2)*(wave_points - 4)) - (3 - i));
				indices_flex.push_back((wave_points - 1) * 4);
				indices_flex.push_back((wave_points - 1) * 4 + 2);
			}
			else
			{
				//indices_flex.push_back(vertices_flex.size() / 6 - 1);
				//indices_flex.push_back((wave_points * 4 - 6));
				//indices_flex.push_back((wave_points - 1) * 6 - ((i + 1) * 2));

				indices_flex.push_back(start_of_midpoints + (wave_points+(wave_points-2)*(wave_points-4))-(3-i));
				indices_flex.push_back(start_of_midpoints + (wave_points+(wave_points-2)*(wave_points-4))-(2-i));
				indices_flex.push_back((wave_points - 1) * 6 - 2*(1+i));

				indices_flex.push_back(start_of_midpoints + (wave_points + (wave_points - 2)*(wave_points - 4)) - (3 - i));
				indices_flex.push_back((wave_points - 1) * 6 - 2 * (1 + i));
				indices_flex.push_back((wave_points - 1) * 6 - 2 * (1 + i) + 2);
			}
			
			if (i == length_t - 1 && i != 0)
			{
				//indices_flex.push_back((wave_points*4 - 6));
			}
			else
			{
				//indices_flex.push_back(start_of_midpoints + mid_points * (mid_points-1) + i); //+1?
			}

			//indices_flex.push_back((wave_points-1)*6 - ((i+1)*2));

			
			/*if (i != 0)
			{
				indices_flex.push_back(vertices_flex.size() / 6 - 1);
			}
			else
			{
				indices_flex.push_back(start_of_midpoints - 4);
			}

			indices_flex.push_back((wave_points - 1) * 6 - ((i + 1) * 2));
			indices_flex.push_back((wave_points - 1) * 6 - ((i) * 2));*/
		}
	}
	else
	{
		for (int i = 0; i < indices_count; i++)
		{
			indices_flex.push_back(i * 2);
			indices_flex.push_back(i * 2 + 1);
			indices_flex.push_back(i * 2 + 3);
			indices_flex.push_back(i * 2);
			indices_flex.push_back(i * 2 + 3);
			indices_flex.push_back(i * 2 + 2);
		}
	}

	/*
	for (int i = 0; i < vertices_flex.size(); i++)
	{
		std::cout << i/6 << "  " << vertices_flex[i] << " ";
		if ((i + 1) % 6 == 0)
			std::cout << "\n";
	}

	for (int i = 0; i < indices_flex.size(); i++)
	{
		std::cout << i/3 << " : " << indices_flex[i] << " ";
		if ((i + 1) % 3 == 0)
			std::cout << "\n";
	}

	std::cout << "indices_flex.size " << indices_flex.size() << "\n";

	std::cout << "vertflex size vs sizeof " << vertices_flex.size() << " " << sizeof(&vertices_flex)*vertices_flex.size() << "\n";
	std::cout << "vertices size vs sizeof " << "24" << " " << sizeof(vertices) << "\n";
	*/
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		0, 2, 3,    // second triangle

		4, 5, 7,
		5, 6, 7
	};

	glm::vec3 positions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f)
	};

	//glfw initialisation
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DBShip", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	unsigned int VBO, VAO, EBO;
	Shader ourShader("Shaders/shader.vs", "Shaders/shader.fs");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices_flex)*vertices_flex.size(), vertices_flex.data(), GL_STATIC_DRAW);
	std::cout << "1: " << vertices << "  2: " << &vertices_flex;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indices_flex)*indices_flex.size(), indices_flex.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//object.Render(vertices);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		current_frame = glfwGetTime();
		delta_time = current_frame - previous_frame;
		total_time += delta_time;
		previous_frame = current_frame;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices_flex)*vertices_flex.size(), vertices_flex.data(), GL_STATIC_DRAW);
		
		if (wave_force != 0)
		{
			for (int i = 0; i < start_of_midpoints; i++) //set i < vertices_flex.size()/6 for top layer only
				vertices_flex[i * 12 + 1] = height[1] + (glm::cos(total_time + 0.0f - vertices_flex[i * 12]) / wave_force);

			for (int i = start_of_midpoints; i < vertices_flex.size() / 6; i++)
			{
				vertices_flex[i * 6 + 1] = height[1] + glm::distance(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(vertices_flex[i * 6], vertices_flex[i * 6 + 1], vertices_flex[i * 6 + 2]))/(40/glm::cos(total_time + glm::distance(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(vertices_flex[i * 6], 0.0f, vertices_flex[i * 6 + 2]))) / wave_force); //(0.0f - vertices_flex[i * 6]) + (0.0f - vertices_flex[i * 6 + 2])
			}
		}
			
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indices_flex)*indices_flex.size(), indices_flex.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// input
		// -----
		ProcessInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// create transformations
		glm::mat4 view;
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
		view = glm::rotate(view, 1.0f, glm::vec3(0.5f, -0.5f, 0.0f));
		// pass transformation matrices to the shader
		ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		ourShader.setMat4("view", view);


		// render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glm::mat4 model;
		model = glm::translate(model, positions[0]);
		float angle = 20.0f;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		ourShader.setMat4("model", model);
		
		glDrawElements(GL_TRIANGLES, indices_flex.size(), GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}