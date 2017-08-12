//
//  Visualizer.cpp
//  FinalProject
//
//  Created by Ronald Brenner on 11.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "Visualizer.hpp"
#include <iostream>
#include <math.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ====================
// Shader source code
// ====================

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";

int Visualizer::doVisualisation() {
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
	
	//	==============
	//	initialize glad -> load function pointers
	//	==============
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//	===============
	//	vertex data
	//	===============
	
	float vertices[] = {
		0.5f, 0.5f, 0.0f,				// top right
		0.5f, -0.5f, 0.0f,				// bottom right
		-0.5f,  -0.5f, 0.0f,			// bottom left
		-0.5f, 0.5f, 0.0f				// top left
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	
	//	==================================
	//	Vertex Array Object (VAO) creation
	//	==================================
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//	=========================================
	//	Vertex Buffer Object (VBO) initialization
	//	=========================================
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//	=========================================
	//	Element Buffer Object (EBO) initialization
	//	=========================================
	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//	===============
	//	shader handling
	//	===============
	
	//	vertex shader
	//	-------------
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//	fragment shader
	//	---------------
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	
	if(!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	//	linking shader-program
	//	----------------------
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	
	glUseProgram(shaderProgram);
	
	//	cleaning shader objects
	//	-----------------------
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	//	=======================
	//	rendering loop starts here
	//	=======================
	while(!glfwWindowShouldClose(window))
	{
		
		// check for input
		// ===============
		processInput(window);
		
		// rendering commands
		// ==================
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//		glDrawArrays(GL_TRIANGLES, 0, 3);     // This is the VBO case
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// check and call events and swap buffers
		// ======================================
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	// glfw: terminate, clearing all previously allocated GLFW resources
	// ====================================================================
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
