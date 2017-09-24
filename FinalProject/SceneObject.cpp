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

void SceneObject::setPath(std::string path)
{
	this->path = path;
}

void SceneObject::draw(ResourceManager &resourceManager)
{
	
	if(this->type != 99 && this->path.empty()) {
		Shader* shader = resourceManager.getShader(this->type);
		shader->use();
		glBindVertexArray(resourceManager.getVAO(this->type));
		glm::mat4 model;
		model = glm::translate(model, this->position);
		model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	} else if (!this->path.empty()) {
		Shader* shader = resourceManager.getShader(99);
		shader->use();
		char *cstr = new char[this->path.length() + 1];
		strcpy(cstr, this->path.c_str());
		Model figure = resourceManager.getFigure(cstr);
		delete [] cstr;
		glm::mat4 model;
		model = glm::translate(model, this->position);
		model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 1.0f, 0.0f));
		if (this->type == 0) {
			model = glm::translate(model, glm::vec3(0.0f, 0.15f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		} else if (this->type == 1) {
			model = glm::translate(model, glm::vec3(0.0f, -0.51f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		} else if (this->type == 2) {
			model = glm::translate(model, glm::vec3(0.0f, 0.67f, 0.0f));
		}
		model = glm::scale(model, resourceManager.getScaling(this->type));
		shader->setMat4("model", model);
		figure.Draw(*shader);
	}
	
	for(std::vector<SceneObject>::iterator it = this->children.begin(); it != this->children.end(); it++) {
		it->draw(resourceManager);
	}
	
}
