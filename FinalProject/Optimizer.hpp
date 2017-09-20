//
//  Optimizer.hpp
//  FinalProject
//
//  Created by Tobias Umlauf on 26.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef Optimizer_hpp
#define Optimizer_hpp

#include <stdio.h>
#include <random>
#include "SceneObject.hpp"

class Optimizer
{
    SceneObject sceneGraph;
    SceneObject modifiedGraph;
    SceneObject currentBestGraph;
    
    double temperature;
    double coolingRate;
    double factor;
    
    double calculateEnergy(SceneObject* sceneGraph);
    void modifySceneGraph();
    double calculateAcceptanceProbability(double currentEnergy, double newEnergy, int temperature);
public:
    Optimizer(SceneObject sceneGraphInput, double temperatureInput, double coolingRateInput);
    SceneObject optimize();
};


#endif /* Optimizer_hpp */
