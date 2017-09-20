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
    
	SceneObject firstChairObject = SceneObject();
	firstChairObject.setType(0);
    firstChairObject.diagLength = sqrtf(0.5);
    firstChairObject.length = 1.0;
    firstChairObject.height = 1.0;
    firstChairObject.width = 1.0;
	
	SceneObject cupboardObject = SceneObject();
	cupboardObject.setType(2);
    cupboardObject.diagLength = sqrtf(0.5);
    cupboardObject.length = 1.0;
    cupboardObject.height = 2.0;
	cupboardObject.width = 1.0;
    
	SceneObject bookObject = SceneObject();
	bookObject.setType(20);
	bookObject.setPosition(glm::vec3(0.0f, 0.725f, 0.0f));
	
	SceneObject tableObject = SceneObject();
	tableObject.setType(1);
    tableObject.setPosition(glm::vec3(1.0f, 0.0f, 1.5f));
    tableObject.diagLength = sqrtf(3.25);
	tableObject.children.push_back(bookObject);
    tableObject.length = 2.0;
    tableObject.height = 1.2;
    tableObject.width = 3.0;
    
	SceneObject wallObject = SceneObject();
	wallObject.setType(11);
	
	SceneObject floorObject = SceneObject();
	floorObject.setType(10);
	floorObject.setPosition(glm::vec3(0.0));
	floorObject.children.push_back(tableObject);
	floorObject.children.push_back(firstChairObject);
    floorObject.children.push_back(firstChairObject);
    floorObject.children.push_back(firstChairObject);
    floorObject.children.push_back(firstChairObject);
	floorObject.children.push_back(cupboardObject);
    floorObject.children.push_back(cupboardObject);
    floorObject.children.push_back(cupboardObject);
    floorObject.children.push_back(cupboardObject);
    
	
	SceneObject rootObject = SceneObject();
	rootObject.setType(99);
	rootObject.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
	rootObject.children.push_back(wallObject);
	rootObject.children.push_back(floorObject);
    rootObject.boundingBox = glm::mat4x2(1, 1, 3, 1,
                                         3, 2, 1, 2);
    
    glm::mat2x2 rot(cos(90 * M_PI/180), sin(90* M_PI/180), -sin(90* M_PI/180), cos(90* M_PI/180));
    glm::mat2x2 rot2(cos(-90 * M_PI/180), sin(-90* M_PI/180), -sin(-90* M_PI/180), cos(-90* M_PI/180));
    //std::cout << cos(90* M_PI/180) << std::endl;
    
    glm::mat4x2 testMat = rot2 * rot * rot * rootObject.boundingBox;
    
    rootObject.boundingBox = rot * rootObject.boundingBox;
    
    glm::vec2 testVec = rootObject.boundingBox[3];
    int testFloat = rootObject.boundingBox[3][1];
    //rootObject.boundingBox[3] -= testVec;
    glm::vec2 testVec2 = rootObject.boundingBox[3];
    
    std::cout << (testFloat % 360) << std::endl;
    
    glm::vec2 center(1.0, 1.5);
    
    glm::vec2 p1(center[0] - (tableObject.length / 2.0),
                 center[1] + (tableObject.width / 2.0));
    glm::vec2 p2(center[0] - (tableObject.length / 2.0),
                 center[1] - (tableObject.width / 2.0));
    glm::vec2 p3(center[0] + (tableObject.length / 2.0),
                 center[1] + (tableObject.width / 2.0));
    glm::vec2 p4(center[0] + (tableObject.length / 2.0),
                 center[1] - (tableObject.width / 2.0));
    
    
    float p1x = cos(45 * M_PI/180) * (p1[0] - center[0]) +  sin(45 * M_PI/180) * (p1[1] - center[1]) + center[0];
    float p1y = -sin(45 * M_PI/180) * (p1[0] - center[0]) + cos(45 * M_PI/180) * (p1[1] - center[1]) + center[1];
    p1[0] = p1x;
    p1[1] = p1y;
    
    float p2x = cos(45 * M_PI/180) * (p2[0] - center[0]) + sin(45 * M_PI/180) * (p2[1] - center[1]) + center[0];
    float p2y = -sin(45 * M_PI/180) * (p2[0] - center[0]) + cos(45 * M_PI/180) * (p2[1] - center[1]) + center[1];
    p2[0] = p2x;
    p2[1] = p2y;
    
    float p3x = cos(45 * M_PI/180) * (p3[0] - center[0]) +  sin(45 * M_PI/180) * (p3[1] - center[1]) + center[0];
    float p3y = -sin(45 * M_PI/180) * (p3[0] - center[0]) + cos(45 * M_PI/180) * (p3[1] - center[1]) + center[1];
    p3[0] = p3x;
    p3[1] = p3y;
    
    float p4x = cos(45 * M_PI/180) * (p4[0] - center[0]) +  sin(45 * M_PI/180) * (p4[1] - center[1]) + center[0];
    float p4y = -sin(45 * M_PI/180) * (p4[0] - center[0]) + cos(45 * M_PI/180) * (p4[1] - center[1]) + center[1];
    p4[0] = p4x;
    p4[1] = p4y;
    
    
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
