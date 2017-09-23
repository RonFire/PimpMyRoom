//
//  Optimizer.cpp
//  FinalProject
//
//  Created by Tobias Umlauf on 26.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "Optimizer.hpp"

inline float sinDeg(float angle)
{
    return  sin(angle * M_PI/180.0);
}

inline float cosDeg(float angle)
{
    return  cos(angle * M_PI/180.0);
}

inline glm::vec2 getRotatedPoint(float angle, float px, float py, float cx, float cy)
{
    return glm::vec2(cosDeg(angle) * (px - cx) + sinDeg(angle) * (py - cy) + cx,
                    -sinDeg(angle) * (px - cx) + cosDeg(angle) * (py - cy) + cy);
}

inline double dot(glm::vec2 u, glm::vec2 v)
{
    return (u.x * v.x + u.y * v.y);
}

inline double norm(glm::vec2 v)
{
    return sqrt(dot(v,v));  // norm = length of  vector
}

inline double dist(glm::vec2 u, glm::vec2 v)
{
    return norm(u - v);
}

inline float getDistanceToNearestWall(glm::vec2 s1, glm::vec2 s2, glm::vec2 p)
{
    //return fabsf((l2y - l1y) * x - (l2x - l1x) * y + l2x * l1y - l2y *l1x) / sqrtf(powf((l2y - l1y), 2.0) + powf((l2x - l1x), 2.0));
    glm::vec2 v = s1 - s2;
    glm::vec2 w = p - s2;
    
    double c1 = dot(w,v);
    if ( c1 <= 0 )
        return dist(p, s2);
    
    double c2 = dot(v,v);
    if ( c2 <= c1 )
        return dist(p, s1);
    
    float b = c1 / c2;
    glm::vec2 p2 = s2 + b * v;
    return dist(p, p2);
}

inline float calculateNearestWallCost(float x, float y, float angle)
{
    float distance = 0.0;
    float smallestDistance = 1000.0;
    float wallOrientation = 0.0;
    float cost = 0.0;
    
    //right wall
    glm::vec2 p1(4.5, -4.5);
    glm::vec2 p2(4.5, 4.5);
    distance = getDistanceToNearestWall(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 180.0;
    }
    //bottom wall
    p1 = glm::vec2(4.5, 4.5);
    p2 = glm::vec2(-4.5, 4.5);
    distance = getDistanceToNearestWall(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 90.0;
    }
    //left wall
    p1 = glm::vec2(-4.5, -4.5);
    p2 = glm::vec2(-4.5, 4.5);
    distance = getDistanceToNearestWall(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 0.0;
    }
    //top wall
    p1 = glm::vec2(4.5, -4.5);
    p2 = glm::vec2(-4.5, -4.5);
    distance = getDistanceToNearestWall(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 270.0;
    }
    
    cost = smallestDistance;
    cost += fabsf(wallOrientation - angle) * 0.05;
    
    return cost;
}

inline float calculateTableDistanceCost(glm::mat4x2 boundingBox, glm::vec3 center, glm::vec3 comparePosition, float compareAngle)
{
    float distance = 0.0;
    float smallestDistance = 1000.0;
    
    glm::vec2 p1 = boundingBox[0];
    glm::vec2 p2 = boundingBox[1];
    glm::vec2 p3 = boundingBox[2];
    glm::vec2 p4 = boundingBox[3];
    
    float x = p1.x;
    float y = p1.y;
    
    distance = getDistanceToNearestWall(p1, p2, glm::vec2(comparePosition.x, comparePosition.z));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
    }
    
    distance = getDistanceToNearestWall(p2, p3, glm::vec2(comparePosition.x, comparePosition.z));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
    }
    
    distance = getDistanceToNearestWall(p3, p4, glm::vec2(comparePosition.x, comparePosition.z));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
    }
    
    distance = getDistanceToNearestWall(p4, p1, glm::vec2(comparePosition.x, comparePosition.z));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
    }
    
    double dotp = dot(glm::vec2(center.x, -center.z), glm::vec2(comparePosition.x, -comparePosition.z));
    double a = dotp / (norm(glm::vec2(center.x, -center.z)) * norm(glm::vec2(comparePosition.x, -comparePosition.z)));
    double angle;
    
    if (a >= 1.0)
    {
        angle =  0.0;
    }
    else if (a <= -1.0)
    {
        angle =  M_PI;
    }
    else
    {
        angle =  acosf(a);
    }
    std::cout << angle << std::endl;
    return fabsf(1.0f - smallestDistance);
}

Optimizer::Optimizer(SceneObject sceneGraphInput, double temperatureInput, double coolingRateInput)
{
    sceneGraph = sceneGraphInput;
    modifiedGraph = sceneGraphInput;
    currentBestGraph = sceneGraphInput;
    temperature = temperatureInput;
    coolingRate = coolingRateInput;
    factor = temperature + 1;
};

double Optimizer::calculateEnergy(SceneObject* sceneGraph)
{
    //SceneObject table = sceneGraph->children[0];
    //SceneObject chair = sceneGraph->children[1];
    
    //double distance = sqrt(pow(table.position[0] - chair.position[0], 2.0) + pow(table.position[2] - chair.position[2], 2.0));
    
    //return pow(4.0 - distance, 2.0);
    
    float cost = 0.0;
    SceneObject currentObject;
    SceneObject compareObject;
    float distanceToPartnerObject;
    float smallestPartnerDistance;
    float distanceToPartnerCost;
    float partnerAngle;
    
    for(int i = 0; i < sceneGraph->children.size(); i++)
    {
        currentObject = sceneGraph->children[i];
        distanceToPartnerObject = 0.0;
        smallestPartnerDistance = 1000.0;
        partnerAngle = 0.0;
        
        for(int j = 0; j < sceneGraph->children.size(); j++)
        {
            compareObject = sceneGraph->children[j];
            if(i != j)
            {
                //distanceToPartnerObject = dist(glm::vec2(currentObject.position.x, currentObject.position.z),
                //                               glm::vec2(compareObject.position.x, compareObject.position.z));
                distanceToPartnerObject = sqrtf(powf(currentObject.position[0] - compareObject.position[0], 2.0) + powf(currentObject.position[2] - compareObject.position[2], 2.0));
                //if(!(currentObject.type == 2 && compareObject.type == 2))
                    cost += fmaxf(0.0, 1.0 - (distanceToPartnerObject / (currentObject.diagLength + compareObject.diagLength)));
                if(currentObject.type == 2 && compareObject.type == 2)
                {
                    if(distanceToPartnerObject < smallestPartnerDistance)
                    {
                        smallestPartnerDistance = distanceToPartnerObject;
                        partnerAngle = compareObject.angle;
                        distanceToPartnerCost = fmaxf(0.0, 1.0 - (distanceToPartnerObject / (currentObject.diagLength + compareObject.diagLength)));
                    }
                }
                if(currentObject.type == 1 && compareObject.type == 0)
                {
                    cost += fabsf((currentObject.diagLength + compareObject.diagLength) - dist(glm::vec2(currentObject.position.x, currentObject.position.z), glm::vec2(compareObject.position.x, compareObject.position.z)));
                   
                    
                    //calculateTableDistanceCost(currentObject.boundingBox, currentObject.position, compareObject.position, compareObject.angle);
                }
            }
        }
        if(currentObject.type == 2)
        {
            cost += 2.0f * calculateNearestWallCost(currentObject.position[0], currentObject.position[2], currentObject.angle);
            cost += 2.0f * fabsf(1.0 - smallestPartnerDistance);
            cost += fabsf(partnerAngle - currentObject.angle) * 0.1f;
            cost -= distanceToPartnerCost;
            
        }
    }
    return cost;
};

void Optimizer::modifySceneGraph()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::normal_distribution<float> distribution(0.0f, (0.3f * temperature/10.0f));
    //std::uniform_real_distribution<> distribution(-4.5, 4.5);
    std::normal_distribution<float> angle(0.0f, temperature * 5.0f);
    
    for(int i = 0; i < modifiedGraph.children.size(); i++)
    {
        while(true)
        {
            glm::vec2 newCenter(modifiedGraph.children[i].position[0], modifiedGraph.children[i].position[2]);
            float objectLength = modifiedGraph.children[i].length;
            float objectWidth = modifiedGraph.children[i].width;
            float oldAngle = modifiedGraph.children[i].angle;
            
            glm::vec2 addVec(distribution(gen), distribution(gen));
            newCenter += addVec;
            
            oldAngle += angle(gen);
            if(oldAngle < 0.0)
                oldAngle += 360.0;
            else
            {
                while(oldAngle > 360.0)
                {
                    oldAngle -= 360.0;
                }
            }
            
            glm::vec2 p1(newCenter[0] - (objectLength / 2.0),
                         newCenter[1] - (objectWidth / 2.0));
            
            glm::vec2 p2(newCenter[0] + (objectLength / 2.0),
                         newCenter[1] - (objectWidth / 2.0));
            
            glm::vec2 p3(newCenter[0] + (objectLength / 2.0),
                         newCenter[1] + (objectWidth / 2.0));
            
            glm::vec2 p4(newCenter[0] - (objectLength / 2.0),
                         newCenter[1] + (objectWidth / 2.0));
            
            p1 = getRotatedPoint(oldAngle, p1[0], p1[1], newCenter[0], newCenter[1]);
            
            //std::cout << p1.x << std::endl;
            
            if(p1[0] < -5.0 || p1[0] > 5.0)
                continue;
            if(p1[1] < -5.0 || p1[1] > 5.0)
                continue;
            
            p2 = getRotatedPoint(oldAngle, p2[0], p2[1], newCenter[0], newCenter[1]);
            if(p2[0] < -5.0 || p2[0] > 5.0)
                continue;
            if(p2[1] < -5.0 || p2[1] > 5.0)
                continue;
            
            p3 = getRotatedPoint(oldAngle, p3[0], p3[1], newCenter[0], newCenter[1]);
            if(p3[0] < -5.0 || p3[0] > 5.0)
                continue;
            if(p3[1] < -5.0 || p3[1] > 5.0)
                continue;
            
            p4 = getRotatedPoint(oldAngle, p4[0], p4[1], newCenter[0], newCenter[1]);
            if(p4[0] < -5.0 || p4[0] > 5.0)
                continue;
            if(p4[1] < -5.0 || p4[1] > 5.0)
                continue;
            
            modifiedGraph.children[i].boundingBox = glm::mat4x2(p1, p2, p3, p4);
            modifiedGraph.children[i].position[0] = newCenter[0];
            modifiedGraph.children[i].position[2] = newCenter[1];
            modifiedGraph.children[i].setAngle(oldAngle);
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

double Optimizer::calculateAcceptanceProbability(double currentEnergy, double newEnergy, int temp)
{
    // If the new solution is better, accept it
    if (newEnergy < currentEnergy) {
        return 1.0;
    }
    // If the new solution is worse, calculate an acceptance probability
    //std::cout << exp((currentEnergy - newEnergy) / (temperature/10.0)) <<  std::endl;
    //std::cout << (logf(temperature) + 4.606) << std::endl;
    //std::cout << temperature << std::endl;
    //std::cout << (temperature/10.0) << std::endl;
    //std::cout << expf(temperature -2)  << std::endl;
    
    return exp((currentEnergy - newEnergy) / (temperature/1.0f));
};

SceneObject Optimizer::optimize()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> accept(0.0, 1.0);
    
    //calculateEnergy(&sceneGraph);
    
    //std::cout << copy.size() << std::endl;
    std::cout << "initial cost:" << calculateEnergy(&sceneGraph) << std::endl;
    
    while(temperature > 0.0)
    {
        for(int i = 0; i < 100; i++)
        {
            modifySceneGraph();
            double currentEnergy = calculateEnergy(&sceneGraph);
            double newEnergy = calculateEnergy(&modifiedGraph);
            double prob = calculateAcceptanceProbability(currentEnergy, newEnergy, temperature);
            //std::cout << calculateEnergy(&currentBestGraph) << std::endl;
            if (prob > accept(gen))
            {
                sceneGraph = modifiedGraph;
                if(calculateEnergy(&sceneGraph) < calculateEnergy(&currentBestGraph))
                {
                    currentBestGraph = sceneGraph;
                }
                break;
            }
            modifiedGraph = sceneGraph;
        }
        //std::cout << calculateEnergy(&sceneGraph) << std::endl;
        temperature -= coolingRate;
    }
    
    std::cout << "best cost:" << calculateEnergy(&currentBestGraph) << std::endl;
    
    return currentBestGraph;
};
