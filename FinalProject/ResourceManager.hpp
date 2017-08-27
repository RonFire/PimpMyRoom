//
//  ResourceManager.hpp
//  FinalProject
//
//  Created by Ronald Brenner on 25.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include <string>
#include <map>
#include "Shader.hpp"
#include "Model.hpp"
#include "stb_image.hpp"
#include "Camera.hpp"
#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif /* ResourceManager_hpp */

class ResourceManager
{
public:
	
	unsigned int floorVBO, floorVAO, wallVBO, wallVAO, ceilingVBO, ceilingVAO;
	unsigned int doorVBO, doorVAO;
	unsigned int chairVBO, chairVAO, tableVBO, tableVAO, cupboardVBO, cupboardVAO;
	unsigned int bookVBO, bookVAO;
	std::vector<Shader*> shader;
	std::map<std::string, Model> figureMap;
	std::map<std::string, Model>::iterator it;
	ResourceManager();
	~ResourceManager();
	
	void initialize();
	
	unsigned int getVAO(int type);
	Shader* getShader(int type);
	Model& getFigure(char *path);
	glm::vec3 getScaling(int type);
};
