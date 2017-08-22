//
//  SceneObject.cpp
//  FinalProject
//
//  Created by Tobias Umlauf on 22.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "SceneObject.hpp"

SceneObject::SceneObject(Mesh* meshInput, Shader* shaderInput, SceneObject* parentInput) {
    mesh = meshInput;
    shader = shaderInput;
    parent = parentInput;
};

SceneObject::~SceneObject(){};

void SceneObject::addChild(SceneObject* child){
    children.push_back(child);
};

void SceneObject::translate(glm::vec3 vector){
    accumulatedModelMatrix = glm::translate(localModelMatrix, vector);
};

void SceneObject::rotate(GLfloat angle, glm::vec3 axis){
    accumulatedModelMatrix = glm::rotate(localModelMatrix, angle, axis);
};
