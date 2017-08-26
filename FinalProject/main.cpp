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
	
	SceneObject childObject = SceneObject();
	childObject.setType(0);
	childObject.setPosition(glm::vec3(-1.5f,  0.0f, -2.5f));
	childObject.setAngle(45.0);
	
	SceneObject rootObject = SceneObject();
	rootObject.setType(1);
	rootObject.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
	rootObject.setAngle(15.0);
	rootObject.children.push_back(childObject);
	
	
//	==================
//	Visualization part
//	==================

	Visualizer visualizer = Visualizer();
	visualizer.doVisualisation(&rootObject);
	return 0;
	
}
