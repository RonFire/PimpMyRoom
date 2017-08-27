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

// ====================
// Main Function starts here
// ====================

int main(int argc, const char * argv[]) {
	
//  ==================
//	Create Test SceneObject
//	==================
	
	SceneObject firstChairObject = SceneObject();
	firstChairObject.setType(0);
	firstChairObject.setPosition(glm::vec3(-1.5f,  0.0f, -2.5f));
	firstChairObject.setAngle(45.0);
	
	SceneObject cupboardObject = SceneObject();
	cupboardObject.setType(2);
	cupboardObject.setPosition(glm::vec3(1.5f, 0.0f, -1.5f));
	cupboardObject.setAngle(-30.0);
	
	SceneObject tableObject = SceneObject();
	tableObject.setType(1);
	tableObject.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	tableObject.setAngle(15.0);
	
	SceneObject wallObject = SceneObject();
	wallObject.setType(11);
	
	SceneObject floorObject = SceneObject();
	floorObject.setType(10);
	floorObject.setPosition(glm::vec3(0.0));
	floorObject.children.push_back(tableObject);
	floorObject.children.push_back(firstChairObject);
	floorObject.children.push_back(cupboardObject);
	
	SceneObject rootObject = SceneObject();
	rootObject.setType(99);
	rootObject.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
	rootObject.children.push_back(wallObject);
	rootObject.children.push_back(floorObject);
	
	
	
//	==================
//	Visualization part
//	==================

	Visualizer visualizer = Visualizer();
	visualizer.doVisualisation(&rootObject);
	return 0;
	
}
