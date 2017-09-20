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
                cost += fmaxf(0.0, 1.0 - (sqrtf(powf(sceneGraph->children[i].position[0] - sceneGraph->children[j].position[0], 2.0) + powf(sceneGraph->children[i].position[2] - sceneGraph->children[j].position[2], 2.0)) / (sceneGraph->children[i].diagLength + sceneGraph->children[j].diagLength)));
            }
        }
    }
    return cost;
};

void Optimizer::modifySceneGraph()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> room(-4.5, 4.5);
    std::uniform_int_distribution<> angle(-360, 360);
    for(int i = 0; i < modifiedGraph.children.size(); i++)
    {
        while(true)
        {
            
            glm::vec2 newCenter(room(gen), room(gen));
            modifiedGraph.children[i].position[0] = newCenter[0];
            modifiedGraph.children[i].position[2] = newCenter[1];
            float objectLength = modifiedGraph.children[i].length;
            float objectWidth = modifiedGraph.children[i].width;
            int oldAngle = modifiedGraph.children[i].angle;
            oldAngle += angle(gen);
            if(oldAngle < 0.0)
                oldAngle += 360.0;
            else
                oldAngle = (oldAngle % 360);
            modifiedGraph.children[i].setAngle(oldAngle);
            glm::vec2 p1(modifiedGraph.children[i].position[0] - modifiedGraph.children[i].length / 2.0,
                         modifiedGraph.children[i].position[2] - modifiedGraph.children[i].width / 2.0);
            
            glm::vec2 p2(modifiedGraph.children[i].position[0] - modifiedGraph.children[i].length / 2.0,
                         modifiedGraph.children[i].position[2] + modifiedGraph.children[i].width / 2.0);
            
            glm::vec2 p3(modifiedGraph.children[i].position[0] + modifiedGraph.children[i].length / 2.0,
                         modifiedGraph.children[i].position[2] + modifiedGraph.children[i].width / 2.0);
            
            glm::vec2 p4(modifiedGraph.children[i].position[0] + modifiedGraph.children[i].length / 2.0,
                         modifiedGraph.children[i].position[2] - modifiedGraph.children[i].width / 2.0);
            
            p1[0] = cos(oldAngle * M_PI/180.0) * (p1[0] - modifiedGraph.children[i].position[0]) +
            sin(oldAngle * M_PI/180.0) * (p1[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[0];
            p1[1] = -sin(oldAngle * M_PI/180.0) * (p1[0] - modifiedGraph.children[i].position[0]) +
            cos(oldAngle * M_PI/180.0) * (p1[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[2];
            
            if(p1[0] < -5.0 || p1[0] > 5.0)
                continue;
            if(p1[1] < -5.0 || p1[1] > 5.0)
                continue;
            
            p2[0] = cos(oldAngle * M_PI/180.0) * (p2[0] - modifiedGraph.children[i].position[0]) +
            sin(oldAngle * M_PI/180.0) * (p2[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[0];
            p2[1] = -sin(oldAngle * M_PI/180.0) * (p2[0] - modifiedGraph.children[i].position[0]) +
            cos(oldAngle * M_PI/180.0) * (p2[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[2];
            
            if(p2[0] < -5.0 || p2[0] > 5.0)
                continue;
            if(p2[1] < -5.0 || p2[1] > 5.0)
                continue;
            
            p3[0] = cos(oldAngle * M_PI/180.0) * (p3[0] - modifiedGraph.children[i].position[0]) +
            sin(oldAngle * M_PI/180.0) * (p3[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[0];
            p3[1] = -sin(oldAngle * M_PI/180.0) * (p3[0] - modifiedGraph.children[i].position[0]) +
            cos(oldAngle * M_PI/180.0) * (p3[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[2];
            
            if(p3[0] < -5.0 || p3[0] > 5.0)
                continue;
            if(p3[1] < -5.0 || p3[1] > 5.0)
                continue;
            
            p4[0] = cos(oldAngle * M_PI/180.0) * (p4[0] - modifiedGraph.children[i].position[0]) +
            sin(oldAngle * M_PI/180.0) * (p4[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[0];
            p4[1] = -sin(oldAngle * M_PI/180.0) * (p4[0] - modifiedGraph.children[i].position[0]) +
            cos(oldAngle * M_PI/180.0) * (p4[1] - modifiedGraph.children[i].position[2]) + modifiedGraph.children[i].position[2];
            
            if(p4[0] < -5 || p4[0] > 5)
                continue;
            if(p4[1] < -5 || p4[1] > 5)
                continue;
            
            break;
        }
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
