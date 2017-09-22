//
//  SceneObject.cpp
//  FinalProject
//
//  Created by Ronald Brenner on 22.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "SceneObject.hpp"


SceneObject::SceneObject() {
	
}

void SceneObject::setType(unsigned int type)
{
	this->type = type;
}

void SceneObject::setPosition(glm::vec3 position)
{
	this->position = position;
}

void SceneObject::setAngle(GLfloat angle)
{
	this->angle = angle;
}

void SceneObject::draw(ResourceManager &resourceManager)
{
	
	if(this->type != 99) {
		Shader* shader = resourceManager.getShader(this->type);
		shader->use();
		glBindVertexArray(resourceManager.getVAO(this->type));
		glm::mat4 model;
		model = glm::translate(model, this->position);
		model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	for(std::vector<SceneObject>::iterator it = this->children.begin(); it != this->children.end(); it++) {
		it->draw(resourceManager);
	}
	
}

void SceneObject::init()
{
    glm::vec2 p1(position.x - (length / 2.0),
                 position.z - (width / 2.0));
    
    glm::vec2 p2(position.x + (length / 2.0),
                 position.z - (width / 2.0));
    
    glm::vec2 p3(position.x + (length / 2.0),
                 position.z + (width / 2.0));
    
    glm::vec2 p4(position.x - (length / 2.0),
                 position.z + (width / 2.0));
    
    boundingBox = glm::mat4x2(p1, p2, p3, p4);
    diagLength = sqrtf(powf(length, 2.0) + powf(width, 2.0)) / 2.0;
}
