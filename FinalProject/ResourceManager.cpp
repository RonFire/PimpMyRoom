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
}
void ResourceManager::initialize()
{
	// init chair VAO to use later in objects
	float chairVertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
		-1.0f, -0.5f, -1.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -0.5f, -1.5f,  0.0f,  0.0f, -1.0f,  2.0f, 0.0f,
		1.0f,  0.7f, -1.5f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		1.0f,  0.7f, -1.5f,  0.0f,  0.0f, -1.0f,  2.0f, 1.0f,
		-1.0f,  0.7f, -1.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -0.5f, -1.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-1.0f, -0.5f,  1.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		1.0f, -0.5f,  1.5f,  0.0f,  0.0f, 1.0f,   2.0f, 0.0f,
		1.0f,  0.7f,  1.5f,  0.0f,  0.0f, 1.0f,   2.0f, 1.0f,
		1.0f,  0.7f,  1.5f,  0.0f,  0.0f, 1.0f,   2.0f, 1.0f,
		-1.0f,  0.7f,  1.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-1.0f, -0.5f,  1.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-1.0f,  0.7f,  1.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-1.0f,  0.7f, -1.5f, -1.0f,  0.0f,  0.0f,  1.0f, 3.0f,
		-1.0f, -0.5f, -1.5f, -1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		-1.0f, -0.5f, -1.5f, -1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		-1.0f, -0.5f,  1.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  0.7f,  1.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		1.0f,  0.7f,  1.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		1.0f,  0.7f, -1.5f,  1.0f,  0.0f,  0.0f,  1.0f, 3.0f,
		1.0f, -0.5f, -1.5f,  1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		1.0f, -0.5f, -1.5f,  1.0f,  0.0f,  0.0f,  0.0f, 3.0f,
		1.0f, -0.5f,  1.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		1.0f,  0.7f,  1.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-1.0f, -0.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 3.0f,
		1.0f, -0.5f, -1.5f,  0.0f, -1.0f,  0.0f,  2.0f, 3.0f,
		1.0f, -0.5f,  1.5f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		1.0f, -0.5f,  1.5f,  0.0f, -1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f, -0.5f,  1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f, -0.5f, -1.5f,  0.0f, -1.0f,  0.0f,  0.0f, 3.0f,
		
		-1.0f,  0.7f, -1.5f,  0.0f,  1.0f,  0.0f,  0.0f, 3.0f,
		1.0f,  0.7f, -1.5f,  0.0f,  1.0f,  0.0f,  2.0f, 3.0f,
		1.0f,  0.7f,  1.5f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		1.0f,  0.7f,  1.5f,  0.0f,  1.0f,  0.0f,  2.0f, 0.0f,
		-1.0f,  0.7f,  1.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  0.7f, -1.5f,  0.0f,  1.0f,  0.0f,  0.0f, 3.0f
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
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  1.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 2.0f,
		0.5f,  1.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 2.0f,
		-0.5f,  1.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 2.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  1.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 2.0f,
		0.5f,  1.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 2.0f,
		-0.5f,  1.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 2.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		
		-0.5f,  1.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  1.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  1.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		0.5f,  1.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  1.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  1.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		
		-0.5f,  1.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  1.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  1.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  1.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  1.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  1.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
		-4.0f,  -0.5f, -4.0f,  0.0f,  1.0f,  0.0f,  0.0f, 8.0f,
		4.0f,  -0.5f, -4.0f,  0.0f,  1.0f,  0.0f,  8.0f, 8.0f,
		4.0f,  -0.5f,  4.0f,  0.0f,  1.0f,  0.0f,  8.0f, 0.0f,
		4.0f,  -0.5f,  4.0f,  0.0f,  1.0f,  0.0f,  8.0f, 0.0f,
		-4.0f,  -0.5f,  4.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-4.0f,  -0.5f, -4.0f,  0.0f,  1.0f,  0.0f,  0.0f, 8.0f
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
			
  case 10:
			return floorVAO;
		
  default:
			return chairVAO;
	}
}

Shader* ResourceManager::getShader(int type)
{
	switch (type) {
		case 10:
			return this->shader[1];
		default:
			return this->shader[0];
	}
}
