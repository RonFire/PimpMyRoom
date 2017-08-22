//
//  SceneObject.hpp
//  FinalProject
//
//  Created by Ronald Brenner on 22.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class SceneObject
{
public:
	SceneObject* parent = nullptr;
	std::vector<SceneObject*> children = {};
	
	glm::vec3 position = glm::vec3(0.0);
	glm::mat4 model = glm::mat4(1.0);
	
	SceneObject();
	
	void draw(Shader shader);
	
	void addChild(SceneObject* child);
	void translate(glm::vec3 vector);
	void rotate(GLfloat angle, glm::vec3 axis = glm::vec3(0.0, 1.0, 0.0));
	void scaleIsotropic(GLfloat value);
};

#endif /* SceneObject_hpp */
