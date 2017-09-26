//
//  Optimizer.cpp
//  FinalProject
//
//  Created by Tobias Umlauf on 26.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#include "Optimizer.hpp"

//helper function to directly input degree
inline float sinDeg(float angle)
{
    return  sin(angle * M_PI/180.0);
}

//helper function to directly input degree
inline float cosDeg(float angle)
{
    return  cos(angle * M_PI/180.0);
}

//function to return a point (px, py) rotated around another point (cx, cy) by angle degrees
inline glm::vec2 getRotatedPoint(float angle, float px, float py, float cx, float cy)
{
    return glm::vec2(cosDeg(angle) * (px - cx) + sinDeg(angle) * (py - cy) + cx,
                    -sinDeg(angle) * (px - cx) + cosDeg(angle) * (py - cy) + cy);
}

//returns dot product
inline double dot(glm::vec2 u, glm::vec2 v)
{
    return (u.x * v.x + u.y * v.y);
}

//returns norm (=length) of a vector
inline double norm(glm::vec2 v)
{
    return sqrt(dot(v,v));
}

//calculates the distance of two points
inline double dist(glm::vec2 u, glm::vec2 v)
{
    return norm(u - v);
}

//function to return distance of point p to the segment defined by s1 -> s2
//found online: http://geomalgorithms.com/a02-_lines.html
inline float getDistanceToNearestSegment(glm::vec2 s1, glm::vec2 s2, glm::vec2 p)
{
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

//function to return the cost for a cupboard in relation to its nearest wall
inline std::vector<float> calculateNearestWallCost(float x, float y, float angle)
{
    float distance = 0.0;
    float smallestDistance = 1000.0;
    float wallOrientation = 0.0;
    std::vector<float> cost;
    
    //right wall
    glm::vec2 p1(5.0, -5.0);
    glm::vec2 p2(5.0, 5.0);
    distance = getDistanceToNearestSegment(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 270.0;
    }
    //bottom wall
    p1 = glm::vec2(5.0, 5.0);
    p2 = glm::vec2(-5.0, 5.0);
    distance = getDistanceToNearestSegment(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 180.0;
    }
    //left wall
    p1 = glm::vec2(-5.0, -5.0);
    p2 = glm::vec2(-5.0, 5.0);
    distance = getDistanceToNearestSegment(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 90.0;
    }
    //top wall
    p1 = glm::vec2(5.0, -5.0);
    p2 = glm::vec2(-5.0, -5.0);
    distance = getDistanceToNearestSegment(p1, p2, glm::vec2(x, y));
    if(distance < smallestDistance)
    {
        smallestDistance = distance;
        wallOrientation = 0.0;
    }

    cost.push_back(smallestDistance);
    cost.push_back(wallOrientation);
    
    return cost;
}

//constructor
Optimizer::Optimizer(SceneObject sceneGraphInput, double temperatureInput, double coolingRateInput)
{
    sceneGraph = sceneGraphInput;
    modifiedGraph = sceneGraphInput;
    currentBestGraph = sceneGraphInput;
    temperature = temperatureInput;
    coolingRate = coolingRateInput;
};

//energy function calculation
double Optimizer::calculateEnergy(SceneObject* sceneGraph)
{
    SceneObject currentObject;
    SceneObject compareObject;
    float cost = 0.0;
    float distanceToPartnerObject;
    float smallestPartnerDistance;
    float partnerAngle;
    
    for(int i = 0; i < sceneGraph->children.size(); i++)
    {
        currentObject = sceneGraph->children[i];
        smallestPartnerDistance = 1000.0;
        
        for(int j = 0; j < sceneGraph->children.size(); j++)
        {
            compareObject = sceneGraph->children[j];
            
            //cost to keep the door free of objects
            cost += fmaxf(0.0, 1.0 - (sqrtf(powf(currentObject.position[0] - 0.0f, 2.0) + powf(currentObject.position[2] - 4.0f, 2.0)) / (currentObject.diagLength + sqrtf(8.0f)/2.0f)));
            
            //an object should not have costs in relation to itself
            if(i != j)
            {
                //general cost penalizing collision between objects
                distanceToPartnerObject = sqrtf(powf(currentObject.position[0] - compareObject.position[0], 2.0) +
                                                powf(currentObject.position[2] - compareObject.position[2], 2.0));
                cost += fmaxf(0.0, 1.0 - (distanceToPartnerObject / (currentObject.diagLength + compareObject.diagLength)));
                
                //cost penalizing if a cupboard has no close neighbor, cost will be added after checking every other cupboard
                if(currentObject.type == 2 && compareObject.type == 2)
                {
                    if(distanceToPartnerObject < smallestPartnerDistance)
                    {
                        smallestPartnerDistance = distanceToPartnerObject;
                        partnerAngle = compareObject.angle;
                    }
                }
                
                //cost penalizing chairs that are not positioned around the table/centered towards its center
                if(currentObject.type == 1 && compareObject.type == 0)
                {
                    //chairs shall be placed a distance of (tableDiagLength + chairDiagLength) from the table
                    cost += 3 * fabsf((currentObject.diagLength + compareObject.diagLength) - dist(glm::vec2(currentObject.position.x, currentObject.position.z), glm::vec2(compareObject.position.x, compareObject.position.z)));
                    //chairs shall be oriented towards the table
                    float angle = (180.0f/M_PI) * atan2(currentObject.position.x - compareObject.position.x,
                                                        currentObject.position.z - compareObject.position.z);
                    while(angle > 360)
                        angle -= 360;
                    while(angle < 0)
                        angle += 360;
                    float angle2 = compareObject.angle;
                    while(angle2 > 360)
                        angle2 -= 360;
                    while(angle2 < 0)
                        angle2 += 360;
                    cost += fminf(fabs(angle - angle2), 360 - fabs(angle - angle2)) * 0.1;
                }
                //cost penalizing chairs the closer they stand together
                if(currentObject.type == 0 && compareObject.type == 0)
                {
                    if(distanceToPartnerObject < 0.1)
                        cost += 4 * (1/0.1);
                    else
                        cost += 4 * (1 / distanceToPartnerObject);
                }
            }
        }
        
        //second level cost calculation (in this case for books on the table)
        if(currentObject.children.size() != 0)
        {
            for(int k = 0; k < currentObject.children.size(); k++)
            {
                SceneObject childObject = currentObject.children[k];
                float smallestDist = 1000;
                float partnerChildAngle;
                
                for(int l = 0; l < currentObject.children.size(); l++)
                {
                    if(k != l)
                    {
                        SceneObject compareChild = currentObject.children[l];
                        //cost penalizing object collision
                        float distanceToOtherChild = sqrtf(powf(childObject.position[0] - compareChild.position[0], 2.0) +
                                                           powf(childObject.position[2] - compareChild.position[2], 2.0));
                        cost += fmaxf(0.0, 1.0 - (distanceToOtherChild / (childObject.diagLength + compareChild.diagLength)));
                        //saving distance to closest partner object
                        if(distanceToOtherChild < smallestDist)
                        {
                            smallestDist = distanceToOtherChild;
                            partnerChildAngle = compareChild.angle;
                        }
                    }
                }
                //cost penalizing distance from partner, as well as difference in angle
                cost += 2.0f * fabsf(childObject.length - smallestDist) + fabsf(childObject.angle - partnerChildAngle) * 0.0001;
            }
        }
        
        //extra costs for cupboards
        if(currentObject.type == 2)
        {
            std::vector<float> costVec = calculateNearestWallCost(currentObject.position[0], currentObject.position[2], currentObject.angle);

            //cost penalizing difference of distance to target distance (=currentObject.width; objects should stand "shoulder to shoulder")
            cost += 3.0f * fabsf((currentObject.width / 2.0f) - costVec[0]);
            float angle = currentObject.angle;
            while(angle > 360)
                angle -= 360;
            while(angle < 0)
                angle += 360;
            
            cost += fminf(fabsf(costVec[1] - angle), 360 - fabsf(costVec[1] - angle)) * 0.1;
            //check in case we only have one cupboard, so smallestPartnerDistance still has the initial 1000 value
            if(smallestPartnerDistance != 1000)
            {
                while(partnerAngle > 360)
                    partnerAngle -= 360;
                while(partnerAngle < 0)
                    partnerAngle += 360;
                cost += 3.0f * fabsf(currentObject.length - smallestPartnerDistance);
                cost += fminf(fabsf(partnerAngle - angle), 360 - fabsf(partnerAngle - angle)) * 0.1f;
            }
        }
    }
    return cost;
};

//function for generating the next candidate for testing
void Optimizer::modifySceneGraph()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    //using gauss distributions depending on the current temperature
    std::normal_distribution<float> distribution(0.0f, 0.5 * temperature);
    std::normal_distribution<float> angle(0.0f, temperature * 5.0f);
    glm::vec2 addVec;
    float angleChange;
    
    for(int i = 0; i < modifiedGraph.children.size(); i++)
    {
        //calculate a new position and angle for the object until we found one that is valid
        while(true)
        {
            glm::vec2 newCenter(modifiedGraph.children[i].position[0], modifiedGraph.children[i].position[2]);
            float objectLength = modifiedGraph.children[i].length;
            float objectWidth = modifiedGraph.children[i].width;
            float newAngle = modifiedGraph.children[i].angle;
            
            addVec = glm::vec2(distribution(gen), distribution(gen));
            angleChange = angle(gen);
            
            //modify center and angle of object
            newCenter += addVec;
            newAngle += angleChange;
            
            //calculate bounding box
            glm::vec2 p1(newCenter[0] - (objectLength / 2.0),
                         newCenter[1] - (objectWidth / 2.0));
            
            glm::vec2 p2(newCenter[0] + (objectLength / 2.0),
                         newCenter[1] - (objectWidth / 2.0));
            
            glm::vec2 p3(newCenter[0] + (objectLength / 2.0),
                         newCenter[1] + (objectWidth / 2.0));
            
            glm::vec2 p4(newCenter[0] - (objectLength / 2.0),
                         newCenter[1] + (objectWidth / 2.0));
            
            //calculate rotated bounding box according to object angle and test if values are inbounds of the room
            p1 = getRotatedPoint(newAngle, p1[0], p1[1], newCenter[0], newCenter[1]);
            if(p1[0] < -5.0 || p1[0] > 5.0 || p1[1] < -5.0 || p1[1] > 5.0)
                continue;
            
            p2 = getRotatedPoint(newAngle, p2[0], p2[1], newCenter[0], newCenter[1]);
            if(p2[0] < -5.0 || p2[0] > 5.0 || p2[1] < -5.0 || p2[1] > 5.0)
                continue;
            
            p3 = getRotatedPoint(newAngle, p3[0], p3[1], newCenter[0], newCenter[1]);
            if(p3[0] < -5.0 || p3[0] > 5.0 || p3[1] < -5.0 || p3[1] > 5.0)
                continue;
            
            p4 = getRotatedPoint(newAngle, p4[0], p4[1], newCenter[0], newCenter[1]);
            if(p4[0] < -5.0 || p4[0] > 5.0 || p4[1] < -5.0 || p4[1] > 5.0)
                continue;
            
            //if all values are valid, save them and break the while loop
            modifiedGraph.children[i].boundingBox = glm::mat4x2(p1, p2, p3, p4);
            modifiedGraph.children[i].position[0] = newCenter[0];
            modifiedGraph.children[i].position[2] = newCenter[1];
            modifiedGraph.children[i].setAngle(newAngle);
            break;
        }
        
        //same as above for tier 2 (=objects on other objects)
        if(modifiedGraph.children[i].children.size() != 0)
        {
            //using gauss distributions depending on the current temperature with smaller values
            std::normal_distribution<float> childDistr(0.0f, (0.7f * temperature * 0.2));
            
            for(int j = 0; j < modifiedGraph.children[i].children.size(); j++)
            {
                //move and rotate child object with the parent object
                modifiedGraph.children[i].children[j].position[0] += addVec.x;
                modifiedGraph.children[i].children[j].position[2] += addVec.y;
                modifiedGraph.children[i].children[j].angle += angleChange;
                glm::vec2 parentCenter(modifiedGraph.children[i].position.x, modifiedGraph.children[i].position.z);
                float parentAngle = modifiedGraph.children[i].angle;
                
                while(true)
                {
                    glm::vec2 childCenter(modifiedGraph.children[i].children[j].position[0],
                                          modifiedGraph.children[i].children[j].position[2]);
                    float childAngle = modifiedGraph.children[i].children[j].angle;
                    
                    float childLength = modifiedGraph.children[i].children[j].length;
                    float childWidth = modifiedGraph.children[i].children[j].width;
                    
                    float objectLength = modifiedGraph.children[i].length / 2.0f;
                    float objectWidth = modifiedGraph.children[i].width / 2.0f;
                    
                    //move child center towards origin, subtract angle of parent object
                    childCenter -= parentCenter;
                    childCenter = getRotatedPoint(-parentAngle, childCenter[0], childCenter[1], 0, 0);
                    childAngle -= parentAngle;
                    
                    //modify center & angle of child
                    childCenter += glm::vec2(childDistr(gen), childDistr(gen));
                    childAngle += angle(gen);
                    
                    //test if new position is inside bounds of parent object
                    //get bounding box points
                    glm::vec2 p1(childCenter[0] - (childLength / 2.0),
                                 childCenter[1] - (childWidth / 2.0));
                    
                    glm::vec2 p2(childCenter[0] + (childLength / 2.0),
                                 childCenter[1] - (childWidth / 2.0));
                    
                    glm::vec2 p3(childCenter[0] + (childLength / 2.0),
                                 childCenter[1] + (childWidth / 2.0));
                    
                    glm::vec2 p4(childCenter[0] - (childLength / 2.0),
                                 childCenter[1] + (childWidth / 2.0));
                    
                    //calculate rotated bounding box according to object angle and test if values are inbounds of parent bounds
                    p1 = getRotatedPoint(childAngle, p1[0], p1[1], childCenter.x, childCenter.y);
                    if(p1[0] < -objectLength || p1[0] > objectLength || p1[1] < -objectWidth || p1[1] > objectWidth)
                        continue;
                    
                    p2 = getRotatedPoint(childAngle, p2[0], p2[1], childCenter.x, childCenter.y);
                    if(p2[0] < -objectLength || p2[0] > objectLength || p2[1] < -objectWidth || p2[1] > objectWidth)
                        continue;
                    
                    p3 = getRotatedPoint(childAngle, p3[0], p3[1], childCenter.x, childCenter.y);
                    if(p3[0] < -objectLength || p3[0] > objectLength || p3[1] < -objectWidth || p3[1] > objectWidth)
                        continue;
                    
                    p4 = getRotatedPoint(childAngle, p4[0], p4[1], childCenter.x, childCenter.y);
                    if(p4[0] < -objectLength || p4[0] > objectLength || p4[1] < -objectWidth || p4[1] > objectWidth)
                        continue;
                    
                    childCenter = getRotatedPoint(parentAngle, childCenter[0], childCenter[1], 0, 0);
                    
                    //move child center back according to parent position & angle
                    childCenter += parentCenter;
                    childAngle += parentAngle;
                    //save new position and angle for child object
                    modifiedGraph.children[i].children[j].position[0] = childCenter[0];
                    modifiedGraph.children[i].children[j].position[2] = childCenter[1];
                    modifiedGraph.children[i].children[j].setAngle(childAngle);
                    break;
                }
            }
        }
    }
};

double Optimizer::calculateAcceptanceProbability(double currentEnergy, double newEnergy)
{
    // If the new solution is better, accept it
    if (newEnergy < currentEnergy) {
        return 1.0;
    }
    //else calculate acceptance probability according to difference of solutions and temperature
    return exp((currentEnergy - newEnergy) / (temperature * 2.0));
};

SceneObject Optimizer::optimize()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> accept(0.0, 1.0);

    std::cout << "Initial cost: " << calculateEnergy(&sceneGraph) << std::endl;
    
    //main loop of the algorithm, as long as the temperature is greater that zero,
    //generate new candidates and evaluate them
    while(temperature > 0.0)
    {
        //we try to find an accepted new candidate 100 times, else we take the old graph
        for(int i = 0; i < 100; i++)
        {
            modifySceneGraph();
            double currentEnergy = calculateEnergy(&sceneGraph);
            double newEnergy = calculateEnergy(&modifiedGraph);
            double prob = calculateAcceptanceProbability(currentEnergy, newEnergy);
            
            //if a worse solution is accepted or a better one is found, save it and break the for loop
            if (prob > accept(gen))
            {
                sceneGraph = modifiedGraph;
                if(calculateEnergy(&sceneGraph) < calculateEnergy(&currentBestGraph))
                {
                    currentBestGraph = sceneGraph;
                }
                break;
            }
            //else, reset the modification
            modifiedGraph = sceneGraph;
        }
        //std::cout << calculateEnergy(&sceneGraph) << std::endl;
        //reduce the temperature afterwards
        temperature -= coolingRate;
    }
    
    std::cout << "Best cost: " << calculateEnergy(&currentBestGraph) << std::endl;
    
    return currentBestGraph;
};
