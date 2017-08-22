//
//  SceneObject.hpp
//  FinalProject
//
//  Created by Tobias Umlauf on 22.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include "Mesh.hpp"

class SceneObject {
public:
    SceneObject* parent = nullptr;
    std::vector<SceneObject*> children = {};
    
    Mesh* mesh;
    Shader* shader;
    SceneObject* parent;
    
    glm::mat4 localModelMatrix = glm::mat4(1);
    glm::mat4 accumulatedModelMatrix = glm::mat4(1);
    
    SceneObject(Mesh* mesh, Shader* shader, SceneObject* parentInput);
    ~SceneObject();
    
    virtual void draw();
    virtual void update(GLfloat deltaTime);
    
    void addChild(SceneObject* child);
    void translate(glm::vec3 vector);
    void rotate(GLfloat angle, glm::vec3 axis);
};

#endif /* SceneObject_hpp */
