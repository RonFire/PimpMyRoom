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
	
	SceneObject tableObject = SceneObject();
	tableObject.setType(1);
	tableObject.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	tableObject.setAngle(15.0);
	
	SceneObject rootObject = SceneObject();
	rootObject.setType(99);
	rootObject.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
	rootObject.children.push_back(tableObject);
	rootObject.children.push_back(firstChairObject);
	
	
	
//	==================
//	Visualization part
//	==================

	Visualizer visualizer = Visualizer();
	visualizer.doVisualisation(&rootObject);
	return 0;
	
}
