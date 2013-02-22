//
//  Obstacle.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#include "Obstacle.h"

using namespace cocos2d;

Obstacle::Obstacle(const char* behaviour)
{
    Obstacle();
}

Obstacle::Obstacle(const char* fileName, const CCPoint position)
{
    Obstacle();
    this->initWithFile(fileName);
    this->setPosition(position);
}