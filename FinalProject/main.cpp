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
#include "SceneObject.hpp"

// ====================
// Main Function starts here
// ====================

int main(int argc, const char * argv[]) {
	
//  ==================
//	Create Test SceneObject
//	==================
	
	SceneObject childObject = SceneObject();
	childObject.translate(glm::vec3(-1.5f,  0.0f, -2.5f));
	
	SceneObject rootObject = SceneObject();
	rootObject.translate(glm::vec3( 2.0f,  0.0f, -15.0f));
	rootObject.addChild(&childObject);
	
	
//	==================
//	Visualization part
//	==================

	Visualizer visualizer = Visualizer();
	visualizer.doVisualisation();
	return 0;
	
}
