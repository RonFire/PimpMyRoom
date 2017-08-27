//
//  main.cpp
//  FinalProject
//
//  Created by Ronald Brenner on 08.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <iostream>
#include "Visualizer.hpp"
#include "Optimizer.hpp"

// ====================
// Main Function starts here
// ====================

int main(int argc, const char * argv[]) {
	
//  ==================
//	Create Test SceneObject
//	==================
    
    SceneObject firstChairObject1 = SceneObject();
    firstChairObject1.setType(0);
    firstChairObject1.diagLength = sqrtf(0.5);
    
    SceneObject firstChairObject2 = SceneObject();
    firstChairObject2.setType(0);
    firstChairObject2.diagLength = sqrtf(0.5);
    
	SceneObject firstChairObject = SceneObject();
	firstChairObject.setType(0);
    firstChairObject.diagLength = sqrtf(0.5);
	//firstChairObject.setPosition(glm::vec3(-1.5f,  0.0f, -2.5f));
	//firstChairObject.setAngle(45.0);
	
	SceneObject cupboardObject = SceneObject();
	cupboardObject.setType(2);
    firstChairObject.diagLength = sqrtf(0.5);
	//cupboardObject.setPosition(glm::vec3(1.5f, 0.0f, -1.5f));
	//cupboardObject.setAngle(-30.0);
	
	SceneObject bookObject = SceneObject();
	bookObject.setType(20);
	bookObject.setPosition(glm::vec3(0.0f, 0.725f, 0.0f));
	//bookObject.setAngle(45.0);
	
	SceneObject tableObject = SceneObject();
	tableObject.setType(1);
    tableObject.diagLength = sqrt(3.25);
	//tableObject.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//tableObject.setAngle(15.0);
	tableObject.children.push_back(bookObject);
	
	SceneObject wallObject = SceneObject();
	wallObject.setType(11);
	
	SceneObject floorObject = SceneObject();
	floorObject.setType(10);
	floorObject.setPosition(glm::vec3(0.0));
	floorObject.children.push_back(tableObject);
	floorObject.children.push_back(firstChairObject);
    floorObject.children.push_back(firstChairObject);
    floorObject.children.push_back(firstChairObject);
	floorObject.children.push_back(cupboardObject);
    
	
	SceneObject rootObject = SceneObject();
	rootObject.setType(99);
	rootObject.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
	rootObject.children.push_back(wallObject);
	rootObject.children.push_back(floorObject);
    rootObject.boundingBox = glm::mat4x2(1, 1, 3, 1,
                                         3, 2, 1, 2);
    
    glm::mat2x2 rot(cos(90 * M_PI/180), sin(90* M_PI/180), -sin(90* M_PI/180), cos(90* M_PI/180));
    
    //std::cout << cos(90* M_PI/180) << std::endl;
    
    rootObject.boundingBox = rot * rootObject.boundingBox;
    
    glm::vec2 testVec = rootObject.boundingBox[1];
    
    
    
    for(int i = 0; i < rootObject.children.size(); i++)
    {
        if(rootObject.children[i].type == 10)
        {
            Optimizer optimizer(rootObject.children[i], 10000, 1);
            rootObject.children[i]  = optimizer.optimize();
        }
    }
	
//	==================
//	Visualization part
//	==================

	Visualizer visualizer = Visualizer();
	visualizer.doVisualisation(&rootObject);
	return 0;
	
}
