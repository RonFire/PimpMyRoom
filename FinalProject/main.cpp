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
	
	SceneObject secondChair = SceneObject();
	secondChair.setType(0);
	secondChair.setPosition(glm::vec3(-1.5f, 0.0f, -1.0f));
	secondChair.setAngle(90.0);
	secondChair.setPath("resource/armchair/Armchair.3ds");
	
	SceneObject cupboardObject = SceneObject();
	cupboardObject.setType(2);
	cupboardObject.setPosition(glm::vec3(1.5f, 0.0f, -1.5f));
	cupboardObject.setAngle(-30.0);
	
	SceneObject secondCupboard = SceneObject();
	secondCupboard.setType(2);
	secondCupboard.setPosition(glm::vec3(4.0f, 0.0f, -2.0f));
	secondCupboard.setAngle(-45.0);
	secondCupboard.setPath("resource/nanosuit/nanosuit.obj");
	
	SceneObject bookObject = SceneObject();
	bookObject.setType(20);
	bookObject.setPosition(glm::vec3(0.0f, 0.725f, 0.0f));
	bookObject.setAngle(45.0);
	
	SceneObject secondBook = SceneObject();
	secondBook.setType(20);
	secondBook.setPosition(glm::vec3(0.3f, 0.725f, -0.7f));
	secondBook.setAngle(23.0);
	
	SceneObject tableObject = SceneObject();
	tableObject.setType(1);
	tableObject.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	tableObject.setAngle(15.0);
	tableObject.children.push_back(bookObject);
	tableObject.children.push_back(secondBook);
	
	SceneObject door = SceneObject();
	door.setType(3);
	door.setPosition(glm::vec3(0.0f, 0.0f, 4.99f));
	
	SceneObject wallObject = SceneObject();
	wallObject.setType(11);
	wallObject.children.push_back(door);
	
	SceneObject ceilingObject = SceneObject();
	ceilingObject.setType(12);
	
	SceneObject floorObject = SceneObject();
	floorObject.setType(10);
	floorObject.setPosition(glm::vec3(0.0));
	floorObject.children.push_back(tableObject);
	floorObject.children.push_back(firstChairObject);
	floorObject.children.push_back(secondChair);
	floorObject.children.push_back(cupboardObject);
	floorObject.children.push_back(secondCupboard);
	
	SceneObject rootObject = SceneObject();
	rootObject.setType(99);
	rootObject.setPosition(glm::vec3( 0.0f,  0.0f,  0.0f));
	rootObject.children.push_back(wallObject);
	rootObject.children.push_back(ceilingObject);
	rootObject.children.push_back(floorObject);
	
	
	
//	==================
//	Visualization part
//	==================

	Visualizer visualizer = Visualizer();
	visualizer.doVisualisation(&rootObject);
	return 0;
	
}
