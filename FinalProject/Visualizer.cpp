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
Camera camera(glm::vec3(0.0, 1.76, 3.0));
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
	// cursor configuration
	// --------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//	===============
	//	vertex data
	//	===============
	
	float vertices[] = {
		// positions          // normals           // texture coords
		-1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f, 0.0f,
		1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		-1.0f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
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
		
		1.0f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		1.0f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		1.0f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		1.0f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		1.0f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		1.0f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  2.0f, 1.0f,
		1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		-1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  2.0f, 1.0f,
		1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	// cube positions
	// --------------
//	glm::vec3 cubePositions[] = {
//		glm::vec3( 0.0f,  0.0f,  0.0f),
//		glm::vec3( 2.0f,  0.0f, -15.0f),
//		glm::vec3(-1.5f,  0.0f, -2.5f),
//		glm::vec3(-3.8f,  0.0f, -12.3f),
//		glm::vec3( 2.4f,  0.0f, -3.5f)
//	};
	
	glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.7f,  3.0f,  2.0f),
		glm::vec3( 2.3f,  3.0f, -4.0f),
		glm::vec3(-4.0f,  3.0f, -12.0f),
		glm::vec3( 0.0f,  3.0f, -3.0f)
	};
	
	//	==================================
	//	Vertex Array Object (VAO) creation
	//	==================================
	
	//	=========================================
	//	Vertex Buffer Object (VBO) initialization
	//	=========================================
	
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	
//	glBindVertexArray(VAO);
//	
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// normal attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	// texture coord attribute !!!! NICHT VERGESSEN !!!!
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
	
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

	
	//	=========================================
	//	Element Buffer Object (EBO) initialization
	//	=========================================
	
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
	
	//	===============
	//	shader handling
	//	===============
	
	Shader boxShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
	Shader lampShader("shaders/LampVertexShader.glsl", "shaders/LampFragmentShader.glsl");
//	Shader modelShader("shaders/ModelVertexShader.glsl", "shaders/ModelFragmentShader.glsl");
	
	// ===============
	// Texture Code
	// ===============
	unsigned int diffuseMap = loadTexture("resource/textures/container.png");
	unsigned int specularMap = loadTexture("resource/textures/container_specular.png");
	
//	Model ourModel("resource/armchair/Armchair.3ds");
	
	boxShader.use();
	boxShader.setInt("material.diffuse", 0);
	boxShader.setInt("material.specular", 1);
	
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
		
		//		glDrawArrays(GL_TRIANGLES, 0, 3);     // This is the VBO case
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		
		// ====================
		// example Camera configuration
		// ====================
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
		// point light 3
		boxShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		boxShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setFloat("pointLights[2].constant", 1.0f);
		boxShader.setFloat("pointLights[2].linear", 0.09);
		boxShader.setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		boxShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		boxShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setFloat("pointLights[3].constant", 1.0f);
		boxShader.setFloat("pointLights[3].linear", 0.09);
		boxShader.setFloat("pointLights[3].quadratic", 0.032);
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
		
//		glBindVertexArray(resourceManager.getVAO(1));
		// model matrix
		// ------------
//		glm::mat4 model;
		// passing transformation to shader
//		boxShader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
//		for (unsigned int i=0; i<(sizeof(cubePositions)/sizeof(*cubePositions)); i++) {
//			glm::mat4 model;
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
//			boxShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
		sceneObject->draw(boxShader, resourceManager);
		
//		lampShader.use();
//		lampShader.setMat4("projection", projection);
//		lampShader.setMat4("view", view);
//		for (unsigned int i=0; i<4; i++) {
//			glm::mat4 model;
//			model = glm::mat4();
//			model = glm::translate(model, pointLightPositions[i]);
//			model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0, 1.0, 0.0));
//			model = glm::scale(model, glm::vec3(0.2f));
//			lampShader.setMat4("model", model);
//			
//			glBindVertexArray(lightVAO);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
		
		// render the loaded model
//		boxShader.use();
//		boxShader.setMat4("projection", projection);
//		boxShader.setMat4("view", view);
//		glm::mat4 modelModel;
//		modelModel = glm::translate(modelModel, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//		modelModel = glm::scale(modelModel, glm::vec3(0.02f, 0.02f, 0.02f));	// it's a bit too big for our scene, so scale it down
//		boxShader.setMat4("model", modelModel);
//		ourModel.Draw(boxShader);
		
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// check and call events and swap buffers
		// ======================================
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
//	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
//	glDeleteBuffers(1, &EBO);
	
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










