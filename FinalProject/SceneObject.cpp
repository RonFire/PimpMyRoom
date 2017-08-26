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

void SceneObject::addChild(SceneObject *child)
{
	children.push_back(child);
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

void SceneObject::draw(Shader &shader, ResourceManager &resourceManager)
{
	shader.use();
	glBindVertexArray(resourceManager.getVAO(this->type));
	glm::mat4 model;
	model = glm::translate(model, this->position);
	model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	for(std::vector<SceneObject*>::iterator it = this->children.begin(); it != this->children.end(); it++) {
		(*it)->draw(shader, resourceManager);
	}
	
}
