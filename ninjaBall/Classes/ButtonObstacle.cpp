//
//  ButtonObstacle.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/14/13.
//
//

#include "ButtonObstacle.h"
#include "World.h"
#include "Ninja.h"
#include "SwitchableObject.h"


using namespace cocos2d;

void ButtonObstacle::interactWithWorld(World world)
{
    if (_switchableObject == NULL)
    {
        _switchableObject = this->getSwitchable(world.obstacles);
    }
    if (_switchableObject != NULL)
    {
        if (Obstacle::checkHit(world.ninja))
        {
            if (!_switchableObject->isOn()) _switchableObject->on();
        }
        else
        {
            if (_switchableObject->isOn()) _switchableObject->off();
        }
    }
}


SwitchableObject* ButtonObstacle::getSwitchable(CCArray* obstacles)
{
    Obstacle* result;
    CCObject* obstacleItem;
    CCARRAY_FOREACH(obstacles, obstacleItem)
    {
        if (((Obstacle*)obstacleItem)->getId() == _switchableId)
        {
            result = (Obstacle*) obstacleItem;
        }
    }
    return result;
}