#include "MainGame.h"
#include "Object.h"
#include "Shader.h"
#include "ocean.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Object object;
Ocean ocean;
std::vector<Ocean> oceans;
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

	int number_of_ocean_chunks = 2;
	std::vector<glm::vec3> dimensions;
	std::vector<std::vector<float>> vertices_flex;
	std::vector<std::vector<unsigned int>> indices_flex;
	std::vector<int> start_of_midpoints;
	std::vector<float> wave_force;
	std::vector<unsigned int> vbo_vec, ebo_vec;

	for (int i = 0; i < number_of_ocean_chunks; i++)
	{
		oceans.push_back(Ocean());
		dimensions.push_back(oceans[oceans.size()-1].ReturnDimensions());
		vertices_flex.push_back(oceans[oceans.size() - 1].CreateVertices());
		indices_flex.push_back(oceans[oceans.size() - 1].CreateIndices());
		start_of_midpoints.push_back(oceans[oceans.size() - 1].GetStartOfMidpoints());
		oceans[oceans.size() - 1].SetWaveForce(10.0f);
		wave_force.push_back(oceans[oceans.size() - 1].GetWaveForce());
		vbo_vec.push_back(unsigned int());
		ebo_vec.push_back(unsigned int());
	}
	dimensions[1] = { 10.0f,1.0f,10.0f };
	std::cout << "oceans size :  " << oceans.size() << " " << vertices_flex[0].size() << " " << vertices_flex.size() << " " << indices_flex.size() << "\n";

	float width[] = { -1.5f, 1.5f };
	float height[] = { -0.5f, 0.5f };
	float depth[] = { -1.5f, 1.5f };
	float test_coord = 0.0f;

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		0, 2, 3,    // second triangle

		4, 5, 7,
		5, 6, 7
	};

	glm::vec3 positions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(3.0f, 0.0f, 0.0f)
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

	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices_flex)*vertices_flex.size(), vertices_flex.data(), GL_STATIC_DRAW);
	//std::cout << "sizes 1,2 " << vertices_flex.size() << " " << vertices_flex.size() << "\n";
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indices_flex)*indices_flex.size(), indices_flex.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	for (int i = 0; i < number_of_ocean_chunks; i++)
		glGenBuffers(1, &vbo_vec[i]);
	for (int i = 0; i < number_of_ocean_chunks; i++)
		glGenBuffers(1, &ebo_vec[i]);
	glBindVertexArray(VAO);
	for (int i = 0; i < number_of_ocean_chunks; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vec[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices_flex[i])*vertices_flex[i].size(), vertices_flex[i].data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_vec[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indices_flex[i])*indices_flex[i].size(), indices_flex[i].data(), GL_STATIC_DRAW);
	}

	ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

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

	int vbo_size = 0;
	glm::mat4 model[2];
	while (!glfwWindowShouldClose(window))
	{
		current_frame = glfwGetTime();
		delta_time = current_frame - previous_frame;
		total_time += delta_time;
		previous_frame = current_frame;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(VAO);

		vbo_size = 0;
		for (int i = 0; i < number_of_ocean_chunks; i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo_vec[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices_flex[i])*vertices_flex[i].size(), vertices_flex[i].data(), GL_STATIC_DRAW);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_vec[i]);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indices_flex[i])*indices_flex[i].size(), indices_flex[i].data(), GL_STATIC_DRAW);
		}

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
		for (int i = 0; i < number_of_ocean_chunks; i++)
		{
			//glm::mat4 model;
			vertices_flex[i] = oceans[i].UpdateVertices(total_time, dimensions[i][1]);
			model[i] = glm::translate(model[i], positions[i]);
			float angle = 20.0f;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model[i]);
			glDrawElements(GL_TRIANGLES, indices_flex[i].size(), GL_UNSIGNED_INT, 0);

		}
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