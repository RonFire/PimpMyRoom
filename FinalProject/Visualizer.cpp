//
//  Visualizer.cpp
//  FinalProject
//
//  Created by Ronald Brenner on 11.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "Visualizer.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0, 1.26, 3.0));  // imitates height of 1.76m
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f; // time of last frame


// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int Visualizer::doVisualisation(SceneObject *sceneObject) {
	//	=====================
	//	glfw: initialize and config
	//	=====================
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to make this Code compatible for multiple platforms
#endif
	
	//	==============
	//	glfw window creation
	//	==============
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FinalProject", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	
	//	==============
	//	initialize glad -> load function pointers
	//	==============
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	// cursor configuration
	// --------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//	===============
	//	vertex data for pointlights
	//	===============
	
	float vertices[] = {
		// positions          // normals           // texture coords
		1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f, 0.0f,
		-1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		-1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		-1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-1.0f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		1.0f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   2.0f, 0.0f,
		1.0f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   2.0f, 1.0f,
		1.0f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   2.0f, 1.0f,
		-1.0f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-1.0f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-1.0f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-1.0f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-1.0f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		1.0f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		1.0f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		1.0f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		1.0f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		1.0f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		1.0f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  2.0f, 1.0f,
		1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  2.0f, 1.0f,
		-1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.0f,  3.0f,  2.0f),
		glm::vec3( 0.0f,  3.0f, -2.0f),
	};
	
	//	==================================
	//	Vertex Array Object (VAO) creation
	//	==================================
	
	//	=========================================
	//	Vertex Buffer Object (VBO) initialization
	//	=========================================
	
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO, lightVBO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(lightVAO);
	// set the vertex attributes (only position data for our lamp)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	resourceManager.initialize();
	
	//	===============
	//	shader handling
	//	===============
	
	Shader boxShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
	Shader floorShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
	Shader wallShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
	Shader ceilingShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
	Shader doorShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
	Shader lampShader("shaders/LampVertexShader.glsl", "shaders/LampFragmentShader.glsl");
	Shader modelShader("shaders/ModelVertexShader.glsl", "shaders/ModelFragmentShader.glsl");
	resourceManager.shader.push_back(&boxShader);
	resourceManager.shader.push_back(&floorShader);
	resourceManager.shader.push_back(&wallShader);
	resourceManager.shader.push_back(&ceilingShader);
	resourceManager.shader.push_back(&doorShader);
	resourceManager.shader.push_back(&modelShader);
	
	// ===============
	// Texture Code
	// ===============
	unsigned int diffuseMap = loadTexture("resource/textures/container.png");
	unsigned int specularMap = loadTexture("resource/textures/container_specular.png");
	unsigned int floorDiffuseMap = loadTexture("resource/textures/floor.jpg");
	unsigned int wallDiffuseMap = loadTexture("resource/textures/wall.jpg");
	unsigned int ceilingDiffuseMap = loadTexture("resource/textures/ceiling.jpg");
	unsigned int doorDiffuseMap = loadTexture("resource/textures/door.png");
	
	unsigned int blackSpecularMap = loadTexture("resource/textures/black.png");
	
	// ===========================================
	// Set Texture Positions for different shaders
	// ===========================================
	floorShader.use();
	floorShader.setInt("material.diffuse", 12);
	floorShader.setInt("material.specular", 12);
	
	wallShader.use();
	wallShader.setInt("material.diffuse", 13);
	wallShader.setInt("material.specular", 14);
	
	ceilingShader.use();
	ceilingShader.setInt("material.diffuse", 16);
	ceilingShader.setInt("material.specular", 16);
	
	doorShader.use();
	doorShader.setInt("material.diffuse", 15);
	doorShader.setInt("material.specular", 15);
	
	boxShader.use();
	boxShader.setInt("material.diffuse", 10);
	boxShader.setInt("material.specular", 11);
	
	//	=======================
	//	rendering loop starts here
	//	=======================
	while(!glfwWindowShouldClose(window))
	{
		// per frame time logic
		// ====================
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// check for input
		// ===============
		processInput(window);
		
		// rendering commands
		// ==================
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		// bind textures to GPU
		// ====================
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE11);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE12);
		glBindTexture(GL_TEXTURE_2D, floorDiffuseMap);
		glActiveTexture(GL_TEXTURE13);
		glBindTexture(GL_TEXTURE_2D, wallDiffuseMap);
		glActiveTexture(GL_TEXTURE14);
		glBindTexture(GL_TEXTURE_2D, blackSpecularMap);
		glActiveTexture(GL_TEXTURE15);
		glBindTexture(GL_TEXTURE_2D, doorDiffuseMap);
		glActiveTexture(GL_TEXTURE16);
		glBindTexture(GL_TEXTURE_2D, ceilingDiffuseMap);
		

		// =======================
		// lightsource input for shaders
		// =======================
		boxShader.use();
		boxShader.setVec3("viewPosition", camera.Position);
		boxShader.setFloat("material.shininess", 32.0f);
		
		// point light 1
		boxShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		boxShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setFloat("pointLights[0].constant", 1.0f);
		boxShader.setFloat("pointLights[0].linear", 0.09);
		boxShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		boxShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		boxShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setFloat("pointLights[1].constant", 1.0f);
		boxShader.setFloat("pointLights[1].linear", 0.09);
		boxShader.setFloat("pointLights[1].quadratic", 0.032);
		
		// view matrix with camera
		// -----------------------
		glm::mat4 view;
		view = camera.GetViewMatrix();
		boxShader.setMat4("view", view);
		// projection matrix
		// -----------------
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
		boxShader.setMat4("projection", projection);
		
		floorShader.use();
		floorShader.setVec3("viewPosition", camera.Position);
		floorShader.setFloat("material.shininess", 32.0f);
		
		// point light 1
		floorShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		floorShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		floorShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		floorShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		floorShader.setFloat("pointLights[0].constant", 1.0f);
		floorShader.setFloat("pointLights[0].linear", 0.09);
		floorShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		floorShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		floorShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		floorShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		floorShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		floorShader.setFloat("pointLights[1].constant", 1.0f);
		floorShader.setFloat("pointLights[1].linear", 0.09);
		floorShader.setFloat("pointLights[1].quadratic", 0.032);
		
		// view matrix with camera
		// -----------------------
		floorShader.setMat4("view", view);
		// projection matrix
		// -----------------
		floorShader.setMat4("projection", projection);
		
		wallShader.use();
		wallShader.setVec3("viewPosition", camera.Position);
		wallShader.setFloat("material.shininess", 32.0f);
		
		// point light 1
		wallShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		wallShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		wallShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		wallShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		wallShader.setFloat("pointLights[0].constant", 1.0f);
		wallShader.setFloat("pointLights[0].linear", 0.09);
		wallShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		wallShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		wallShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		wallShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		wallShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		wallShader.setFloat("pointLights[1].constant", 1.0f);
		wallShader.setFloat("pointLights[1].linear", 0.09);
		wallShader.setFloat("pointLights[1].quadratic", 0.032);
		
		// view matrix with camera
		// -----------------------
		wallShader.setMat4("view", view);
		// projection matrix
		// -----------------
		wallShader.setMat4("projection", projection);
		
		ceilingShader.use();
		ceilingShader.setVec3("viewPosition", camera.Position);
		ceilingShader.setFloat("material.shininess", 32.0f);
		
		// point light 1
		ceilingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		ceilingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		ceilingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		ceilingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		ceilingShader.setFloat("pointLights[0].constant", 1.0f);
		ceilingShader.setFloat("pointLights[0].linear", 0.09);
		ceilingShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		ceilingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		ceilingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		ceilingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		ceilingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		ceilingShader.setFloat("pointLights[1].constant", 1.0f);
		ceilingShader.setFloat("pointLights[1].linear", 0.09);
		ceilingShader.setFloat("pointLights[1].quadratic", 0.032);
		
		// view matrix with camera
		// -----------------------
		ceilingShader.setMat4("view", view);
		// projection matrix
		// -----------------
		ceilingShader.setMat4("projection", projection);
		
		doorShader.use();
		doorShader.setVec3("viewPosition", camera.Position);
		doorShader.setFloat("material.shininess", 32.0f);
		
		// point light 1
		doorShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		doorShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		doorShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		doorShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		doorShader.setFloat("pointLights[0].constant", 1.0f);
		doorShader.setFloat("pointLights[0].linear", 0.09);
		doorShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		doorShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		doorShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		doorShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		doorShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		doorShader.setFloat("pointLights[1].constant", 1.0f);
		doorShader.setFloat("pointLights[1].linear", 0.09);
		doorShader.setFloat("pointLights[1].quadratic", 0.032);
		
		// view matrix with camera
		// -----------------------
		doorShader.setMat4("view", view);
		// projection matrix
		// -----------------
		doorShader.setMat4("projection", projection);
		
		modelShader.use();
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);
		
		sceneObject->draw(resourceManager);
		
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		for (unsigned int i=0; i<2; i++) {
			glm::mat4 model;
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0, 1.0, 0.0));
			model = glm::scale(model, glm::vec3(0.2f));
			lampShader.setMat4("model", model);
			
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// check and call events and swap buffers
		// ======================================
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	
	// glfw: terminate, clearing all previously allocated GLFW resources
	// ====================================================================
	glfwTerminate();
	return 0;
}


//=======================================================
// Callbacks and utility functions
//=======================================================

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ======================================================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// ==============================================================
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	
	camera.ProcessMouseMovement(xoffset, yoffset);
}
// ==============================================================
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ====================================================================================================
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	
	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	
	return textureID;
}










