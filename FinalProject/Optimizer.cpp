//
//  Optimizer.cpp
//  FinalProject
//
//  Created by Tobias Umlauf on 26.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "Optimizer.hpp"

Optimizer::Optimizer(SceneObject sceneGraphInput, double temperatureInput, double coolingRateInput)
{
    sceneGraph = sceneGraphInput;
    modifiedGraph = sceneGraphInput;
    currentBestGraph = sceneGraphInput;
    temperature = temperatureInput;
    coolingRate = coolingRateInput;
};

double Optimizer::calculateEnergy(SceneObject* sceneGraph)
{
    //SceneObject table = sceneGraph->children[0];
    //SceneObject chair = sceneGraph->children[1];
    
    //double distance = sqrt(pow(table.position[0] - chair.position[0], 2.0) + pow(table.position[2] - chair.position[2], 2.0));
    
    //return pow(4.0 - distance, 2.0);
    
    float cost = 0.0;
    
    for(int i = 0; i < sceneGraph->children.size(); i++)
    {
        for(int j = 0; j < sceneGraph->children.size(); j++)
        {
            if(i != j)
            {
                cost += fmaxf(0.0, 1.0 - sqrt(pow(sceneGraph->children[i].position[0] - sceneGraph->children[j].position[0], 2.0) + pow(sceneGraph->children[i].position[2] - sceneGraph->children[j].position[2], 2.0)) / (sceneGraph->children[i].diagLength + sceneGraph->children[j].diagLength));
            }
        }
    }
    return cost;
};

void Optimizer::modifySceneGraph()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> room(-4.0, 4.0);
    std::uniform_int_distribution<> angle(0, 360);
    for(int i = 0; i < modifiedGraph.children.size(); i++)
    {
        modifiedGraph.children[i].position[0] = room(gen);
        modifiedGraph.children[i].position[2] = room(gen);
        modifiedGraph.children[i].setAngle(angle(gen));
        if(modifiedGraph.children[i].children.size() != 0)
        {
            for(int j = 0; j < modifiedGraph.children[i].children.size(); j++)
            {
                modifiedGraph.children[i].children[j].position[0] = modifiedGraph.children[i].position[0];
                modifiedGraph.children[i].children[j].position[2] = modifiedGraph.children[i].position[2];
                modifiedGraph.children[i].children[j].setAngle(angle(gen));
            }
        }
    }
};

double Optimizer::calculateAcceptanceProbability(double currentEnergy, double newEnergy, int temperature)
{
    // If the new solution is better, accept it
    if (newEnergy < currentEnergy) {
        return 1.0;
    }
    // If the new solution is worse, calculate an acceptance probability
    return exp((currentEnergy - newEnergy) / temperature);
};

SceneObject Optimizer::optimize()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> accept(0, 1);
    
    calculateEnergy(&sceneGraph);
    
    //std::cout << copy.size() << std::endl;
    std::cout << "initial cost:" << calculateEnergy(&sceneGraph) << std::endl;
    
    while(temperature > 1.0)
    {
        modifySceneGraph();
        double currentEnergy = calculateEnergy(&sceneGraph);
        double newEnergy = calculateEnergy(&modifiedGraph);
        double prob = calculateAcceptanceProbability(currentEnergy, newEnergy, temperature);
        //std::cout << calculateEnergy(&currentBestGraph) << std::endl;
        if (prob > accept(gen)) {
            sceneGraph = modifiedGraph;
        }
        modifiedGraph = sceneGraph;
        
        if(calculateEnergy(&sceneGraph) < calculateEnergy(&currentBestGraph))
        {
            currentBestGraph = sceneGraph;
        }
        
        temperature -= coolingRate;
    }
    
    std::cout << "best cost:" << calculateEnergy(&currentBestGraph) << std::endl;
    
    return currentBestGraph;
};
