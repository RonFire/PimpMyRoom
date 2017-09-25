//
//  ResourceManager.cpp
//  FinalProject
//
//  Created by Ronald Brenner on 25.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{
	
}
ResourceManager::~ResourceManager()
{
	glDeleteVertexArrays(1, &chairVAO);
	glDeleteVertexArrays(1, &tableVAO);
	glDeleteBuffers(1, &chairVBO);
	glDeleteBuffers(1, &tableVBO);
	glDeleteVertexArrays(1, &cupboardVAO);
	glDeleteBuffers(1, &cupboardVBO);
	glDeleteVertexArrays(1, &floorVAO);
	glDeleteBuffers(1, &floorVBO);
	glDeleteVertexArrays(1, &wallVAO);
	glDeleteBuffers(1, &wallVBO);
	glDeleteVertexArrays(1, &ceilingVAO);
	glDeleteBuffers(1, &ceilingVBO);
	glDeleteVertexArrays(1, &doorVAO);
	glDeleteBuffers(1, &doorVBO);
	glDeleteVertexArrays(1, &bookVAO);
	glDeleteBuffers(1, &bookVBO);
	
}
void ResourceManager::initialize()
{
	// init book VAO to use later in objects
	float bookVertices[] = {
		// positions          // normals           // texture coords
		0.15f, -0.025f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		-0.15f, -0.025f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.15f,  0.025f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.15f,  0.025f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		0.15f,  0.025f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.15f, -0.025f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-0.15f, -0.025f,  0.1f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.15f, -0.025f,  0.1f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.15f,  0.025f,  0.1f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.15f,  0.025f,  0.1f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.15f,  0.025f,  0.1f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.15f, -0.025f,  0.1f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-0.15f,  0.025f,  0.1f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.15f,  0.025f, -0.1f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.15f, -0.025f, -0.1f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.15f, -0.025f, -0.1f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.15f, -0.025f,  0.1f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.15f,  0.025f,  0.1f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		0.15f,  0.025f, -0.1f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.15f,  0.025f,  0.1f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.15f, -0.025f, -0.1f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.15f, -0.025f,  0.1f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.15f, -0.025f, -0.1f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.15f,  0.025f,  0.1f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-0.15f, -0.025f, -0.1f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.15f, -0.025f, -0.1f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.15f, -0.025f,  0.1f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.15f, -0.025f,  0.1f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.15f, -0.025f,  0.1f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.15f, -0.025f, -0.1f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		0.15f,  0.025f, -0.1f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		-0.15f,  0.025f, -0.1f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.15f,  0.025f,  0.1f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.15f,  0.025f,  0.1f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		0.15f,  0.025f,  0.1f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.15f,  0.025f, -0.1f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	
	glGenVertexArrays(1, &bookVAO);
	glGenBuffers(1, &bookVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, bookVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bookVertices), bookVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(bookVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// init chair VAO to use later in objects
	float chairVertices[] = {
		// positions          // normals           // texture coords
		-0.7f, -0.5f, -0.72f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.7f, -0.5f, -0.72f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.7f,  0.5f, -0.72f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.7f,  0.5f, -0.72f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.7f,  0.5f, -0.72f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.7f, -0.5f, -0.72f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-0.7f, -0.5f,  0.72f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.7f, -0.5f,  0.72f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.7f,  0.5f,  0.72f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.7f,  0.5f,  0.72f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.7f,  0.5f,  0.72f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.7f, -0.5f,  0.72f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-0.7f,  0.5f,  0.72f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.7f,  0.5f, -0.72f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.7f, -0.5f, -0.72f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.7f, -0.5f, -0.72f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.7f, -0.5f,  0.72f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.7f,  0.5f,  0.72f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		0.7f,  0.5f,  0.72f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.7f,  0.5f, -0.72f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.7f, -0.5f, -0.72f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.7f, -0.5f, -0.72f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.7f, -0.5f,  0.72f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.7f,  0.5f,  0.72f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-0.7f, -0.5f, -0.72f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.7f, -0.5f, -0.72f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.7f, -0.5f,  0.72f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.7f, -0.5f,  0.72f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.7f, -0.5f,  0.72f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.7f, -0.5f, -0.72f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		-0.7f,  0.5f, -0.7f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.7f,  0.5f, -0.7f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.7f,  0.5f,  0.7f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.7f,  0.5f,  0.7f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.7f,  0.5f,  0.7f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.7f,  0.5f, -0.7f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	
	glGenVertexArrays(1, &chairVAO);
	glGenBuffers(1, &chairVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, chairVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(chairVertices), chairVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(chairVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// init tableVAO for later use
	float tableVertices[] = {
		// positions          // normals           // texture coords
		0.81f, -0.5f, -1.41f,  0.0f,  0.0f, -1.0f,  2.0f, 0.0f,
		-0.81f, -0.5f, -1.41f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.81f,  0.7f, -1.41f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		-0.81f,  0.7f, -1.41f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		0.81f,  0.7f, -1.41f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		-0.81f, -0.5f, -1.41f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-0.81f, -0.5f,  1.41f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.81f, -0.5f,  1.41f,  0.0f,  0.0f, 1.0f,   2.0f, 0.0f,
		0.81f,  0.7f,  1.41f,  0.0f,  0.0f, 1.0f,   2.0f, 1.0f,
		0.81f,  0.7f,  1.41f,  0.0f,  0.0f, 1.0f,   2.0f, 1.0f,
		-0.81f,  0.7f,  1.41f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.81f, -0.5f,  1.41f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-0.81f,  0.7f,  1.41f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.81f,  0.7f, -1.41f, -1.0f,  0.0f,  0.0f,  1.0f, 3.0f,
		-0.81f, -0.5f, -1.41f, -1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		-0.81f, -0.5f, -1.41f, -1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		-0.81f, -0.5f,  1.41f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.81f,  0.7f,  1.41f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		0.81f,  0.7f, -1.41f,  1.0f,  0.0f,  0.0f,  1.0f, 3.0f,
		0.81f,  0.7f,  1.41f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.81f, -0.5f, -1.41f,  1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		0.81f, -0.5f,  1.41f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.81f, -0.5f, -1.41f,  1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		0.81f,  0.7f,  1.41f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-0.81f, -0.5f, -1.41f,  0.0f, -1.0f,  0.0f,  0.0f, 3.0f,
		0.81f, -0.5f, -1.41f,  0.0f, -1.0f,  0.0f,  2.0f, 3.0f,
		0.81f, -0.5f,  1.41f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		0.81f, -0.5f,  1.41f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		-0.81f, -0.5f,  1.41f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.81f, -0.5f, -1.41f,  0.0f, -1.0f,  0.0f,  0.0f, 3.0f,
		
		0.81f,  0.7f, -1.41f,  0.0f,  1.0f,  0.0f,  2.0f, 3.0f,
		-0.81f,  0.7f, -1.41f,  0.0f,  1.0f,  0.0f,  0.0f, 3.0f,
		0.81f,  0.7f,  1.41f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		-0.81f,  0.7f,  1.41f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		0.81f,  0.7f,  1.41f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		-0.81f,  0.7f, -1.41f,  0.0f,  1.0f,  0.0f,  0.0f, 3.0f
	};
	
	glGenVertexArrays(1, &tableVAO);
	glGenBuffers(1, &tableVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, tableVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tableVertices), tableVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(tableVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// init cupboard VAO to use later in objects
	float cupboardVertices[] = {
		// positions          // normals           // texture coords
		-0.63f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.63f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.63f,  1.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 2.0f,
		0.63f,  1.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 2.0f,
		-0.63f,  1.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 2.0f,
		-0.63f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-0.63f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.63f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.63f,  1.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 2.0f,
		0.63f,  1.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 2.0f,
		-0.63f,  1.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 2.0f,
		-0.63f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-0.63f,  1.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.63f,  1.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.63f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.63f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.63f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.63f,  1.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		0.63f,  1.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.63f,  1.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.63f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.63f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.63f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.63f,  1.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-0.63f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.63f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.63f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.63f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.63f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.63f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		-0.63f,  1.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.63f,  1.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.63f,  1.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.63f,  1.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.63f,  1.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.63f,  1.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	
	glGenVertexArrays(1, &cupboardVAO);
	glGenBuffers(1, &cupboardVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, cupboardVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cupboardVertices), cupboardVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(cupboardVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// initialize floor VAO
	float floorVertices[] = {
		// positions          // normals           // texture coords
		5.0f,  -0.5f, -5.0f,  0.0f,  1.0f,  0.0f,  8.0f, 10.0f,
		-5.0f,  -0.5f, -5.0f,  0.0f,  1.0f,  0.0f,  0.0f, 10.0f,
		5.0f,  -0.5f,  5.0f,  0.0f,  1.0f,  0.0f,  8.0f, 0.0f,
		-5.0f,  -0.5f,  5.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		5.0f,  -0.5f,  5.0f,  0.0f,  1.0f,  0.0f,  8.0f, 0.0f,
		-5.0f,  -0.5f, -5.0f,  0.0f,  1.0f,  0.0f,  0.0f, 10.0f
	};
	
	glGenVertexArrays(1, &floorVAO);
	glGenBuffers(1, &floorVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(floorVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// init wall VAO to use later in objects
	float wallVertices[] = {
		// positions          // normals           // texture coords
		-5.0f, -0.5f, -5.0f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
		5.0f, -0.5f, -5.0f,  0.0f,  0.0f, 1.0f,  10.0f, 0.0f,
		5.0f,  3.5f, -5.0f,  0.0f,  0.0f, 1.0f,  10.0f, 3.0f,
		5.0f,  3.5f, -5.0f,  0.0f,  0.0f, 1.0f,  10.0f, 3.0f,
		-5.0f,  3.5f, -5.0f,  0.0f,  0.0f, 1.0f,  0.0f, 3.0f,
		-5.0f, -0.5f, -5.0f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
		
		5.0f, -0.5f,  5.0f,  0.0f,  0.0f, -1.0f,   10.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		5.0f,  3.5f,  5.0f,  0.0f,  0.0f, -1.0f,   10.0f, 3.0f,
		-5.0f,  3.5f,  5.0f,  0.0f,  0.0f, -1.0f,   0.0f, 3.0f,
		5.0f,  3.5f,  5.0f,  0.0f,  0.0f, -1.0f,   10.0f, 3.0f,
		-5.0f, -0.5f,  5.0f,  0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		
		5.0f,  3.5f,  5.0f, -1.0f,  0.0f,  0.0f,  10.0f, 3.0f,
		5.0f,  3.5f, -5.0f, -1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		5.0f, -0.5f, -5.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		5.0f, -0.5f, -5.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		5.0f, -0.5f,  5.0f, -1.0f,  0.0f,  0.0f,  10.0f, 0.0f,
		5.0f,  3.5f,  5.0f, -1.0f,  0.0f,  0.0f,  10.0f, 3.0f,
		
		-5.0f,  3.5f, -5.0f,  1.0f,  0.0f,  0.0f,  10.0f, 3.0f,
		-5.0f,  3.5f,  5.0f,  1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		-5.0f, -0.5f, -5.0f,  1.0f,  0.0f,  0.0f,  10.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  1.0f,  0.0f,  0.0f,  10.0f, 3.0f,
		-5.0f,  3.5f,  5.0f,  1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
	};
	
	
	glGenVertexArrays(1, &wallVAO);
	glGenBuffers(1, &wallVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(wallVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// init ceiling VAO to use later in objects
	float ceilingVertices[] = {
		// positions          // normals           // texture coords
		-5.0f, 3.5f, -5.0f,  0.0f, -1.0f,  0.0f,  0.0f, 10.0f,
		5.0f, 3.5f, -5.0f,  0.0f, -1.0f,  0.0f,  10.0f, 10.0f,
		5.0f, 3.5f,  5.0f,  0.0f, -1.0f,  0.0f,  10.0f, 0.0f,
		5.0f, 3.5f,  5.0f,  0.0f, -1.0f,  0.0f,  10.0f, 0.0f,
		-5.0f, 3.5f,  5.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-5.0f, 3.5f, -5.0f,  0.0f, -1.0f,  0.0f,  0.0f, 10.0f,
	};
	
	
	glGenVertexArrays(1, &ceilingVAO);
	glGenBuffers(1, &ceilingVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, ceilingVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ceilingVertices), ceilingVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(ceilingVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// init door VAO to use later in objects
	float doorVertices[] = {
		// positions          // normals           // texture coords
		-0.6f, 2.0f, 0.0f,  0.0f, 0.0f,  -1.0f,  0.28f, 1.01f,
		0.6f, 2.0f, 0.0f,  0.0f, 0.0f,  -1.0f,  0.72f, 1.01f,
		0.6f, -0.5f,  0.0f,  0.0f, 0.0f,  -1.0f,  0.72f, 0.0f,
		0.6f, -0.5f,  0.0f,  0.0f, 0.0f,  -1.0f,  0.72f, 0.0f,
		-0.6f, -0.5f,  0.0f,  0.0f, 0.0f,  -1.0f,  0.28f, 0.0f,
		-0.6f, 2.0f,  0.0f,  0.0f, 0.0f,  -1.0f,  0.28f, 1.01f,
	};
	
	
	glGenVertexArrays(1, &doorVAO);
	glGenBuffers(1, &doorVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, doorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(doorVertices), doorVertices, GL_STATIC_DRAW);
	
	glBindVertexArray(doorVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

unsigned int ResourceManager::getVAO(int type)
{
	switch (type) {
		case 0:
			return chairVAO;
			
		case 1:
			return tableVAO;
			
		case 2:
			return cupboardVAO;
			
		case 3:
			return doorVAO;
			
		case 10:
			return floorVAO;
			
		case 11:
			return wallVAO;
			
		case 12:
			return ceilingVAO;
			
		case 20:
			return bookVAO;
			
		
  default:
			return chairVAO;
	}
}

Shader* ResourceManager::getShader(int type)
{
	switch (type) {
		case 3:
			return this->shader[4];
		case 10:
			return this->shader[1];
		case 11:
			return this->shader[2];
		case 12:
			return this->shader[3];
		case 99:
			return this->shader[5];
		default:
			return this->shader[0];
	}
}

Model& ResourceManager::getFigure(char *path)
{
	std::map<std::string, Model>::iterator it;
	it = this->figureMap.find(path);
	if (it != this->figureMap.end()) {
		return it->second;
	}
	Model model(path);
	this->figureMap.insert(std::pair<std::string, Model>(path, model));
	return model;
}

glm::vec3 ResourceManager::getScaling(int type)
{
	switch (type) {
		case 0:
			return glm::vec3(1.0f);
		case 1:
			return glm::vec3(0.315f);
		case 2:
			return glm::vec3(0.6f);
		default:
			return glm::vec3(1.0f);
	}
}


