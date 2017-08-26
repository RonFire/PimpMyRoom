//
//  Visualizer.hpp
//  FinalProject
//
//  Created by Ronald Brenner on 11.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef Visualizer_hpp
#define Visualizer_hpp

#include "SceneObject.hpp"

class Visualizer {
	
	
public:
	ResourceManager resourceManager;
	int doVisualisation(SceneObject* sceneObject);
};

#endif /* Visualizer_hpp */
