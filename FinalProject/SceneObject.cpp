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

void SceneObject::translate(glm::vec3 vector)
{
	model = glm::translate(model, vector);
}

void SceneObject::rotate(GLfloat angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
}

void SceneObject::scaleIsotropic(GLfloat value)
{
	model = glm::scale(model, glm::vec3(value));
}
