//
//  ObstaclesController.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#include "ObstaclesController.h"
#include "Obstacle.h"
#include "Settings.h"

using namespace cocos2d;

ObstaclesController::ObstaclesController(CCLayer* mapLayer):MONSTERS_NUM(12)
{
    _obstacles = NULL;
    _mapLayer = mapLayer;
}

void ObstaclesController::clear()
{
    if (_obstacles != NULL)
    {
        CCObject* obstacleItem;
        CCARRAY_FOREACH(_obstacles, obstacleItem)
        {
            if (_mapLayer->getChildren()->containsObject(obstacleItem))
            {
                ((CCSprite*) obstacleItem)->stopAllActions();
                _mapLayer->removeChild((CCSprite*) obstacleItem, true);
            }
        }
        _obstacles->removeAllObjects();
        _obstacles = NULL;
    }
}

bool ObstaclesController::testHit(CCSprite* object)
{
    CCObject* item;
    Obstacle* obstacle;
    CCARRAY_FOREACH(_obstacles, item)
    {
        obstacle = (Obstacle*) item;
        if (obstacle->checkHit(object))
        {
            return true;
        }
    }
    return false;
}

bool ObstaclesController::testDamage(Ninja* ninja)
{
    CCObject* item;
    Obstacle* obstacle;
    CCARRAY_FOREACH(_obstacles, item)
    {
        obstacle = (Obstacle*) item;
        if (obstacle->checkHeroDamage(ninja))
        {
            return true;
        }
    }
    return false;
}

void ObstaclesController::createFromJSON(Json::Value jsonValue)
{
    Obstacle* obstacle;
    Json::Value mapItem;
    for (int i = 0; i < jsonValue.size(); ++i) {
        mapItem = jsonValue[i];
        obstacle = Obstacle::createFromJSON(mapItem);
        if (_obstacles == NULL) { _obstacles = new CCArray(); }
        _obstacles->addObject(obstacle);
        _mapLayer->addChild(obstacle);
    }
}