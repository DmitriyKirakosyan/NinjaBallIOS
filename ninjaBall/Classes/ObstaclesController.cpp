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
#include "TeslaInteraction.h"
#include "TeslaItem.h"
#include "JSONObjstacleFactory.h"

using namespace cocos2d;

ObstaclesController::ObstaclesController(CCLayer* mapLayer):MONSTERS_NUM(12)
{
    _obstacles = NULL;
    _mapLayer = mapLayer;
    _world = World();
    _teslaInteraction = new TeslaInteraction(_mapLayer);
    
//    CCSprite* testSprite = new CCSprite();//CCSprite::create("saw.png");
//    _mapLayer->addChild(testSprite);
//    
//    CCSprite* newtestSprite = CCSprite::create("saw.png");
//    testSprite->addChild(newtestSprite);
}

void ObstaclesController::interact(Ninja* ninja)
{
    CCObject* obstacleItem;
    _world.ninja = ninja;
    _world.obstacles = _obstacles;
    CCARRAY_FOREACH(_obstacles, obstacleItem)
    {
        ((Obstacle*) obstacleItem)->interactWithWorld(_world);
    }
    _teslaInteraction->interact();
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
    _teslaInteraction->clear();
}

bool ObstaclesController::testHit(CCSprite* object)
{
    CCObject* item;
    CCARRAY_FOREACH(_obstacles, item)
    {
        if (((Obstacle*)item)->checkHit(object))
        {
            return true;
        }
    }
    return false;
}

bool ObstaclesController::testHitWithPoint(CCPoint point)
{
    CCObject* item;
    CCARRAY_FOREACH(_obstacles, item)
    {
        if (((Obstacle*) item)->checkHitWithPoint(point))
        {
            return true;
        }
    }
    return false;
}

bool ObstaclesController::isPointPathless(CCPoint point)
{
    CCObject* item;
    CCARRAY_FOREACH(_obstacles, item)
    {
        if (((Obstacle*)item)->pathless() &&
            ((Obstacle*)item)->checkHitWithPoint(point))
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
    return _teslaInteraction->checkDamage(ninja);
}

void ObstaclesController::createFromJSON(Json::Value jsonValue)
{
    //this->clear();
    Obstacle* obstacle;
    Json::Value mapItem;
    for (int i = 0; i < jsonValue.size(); ++i) {
        mapItem = jsonValue[i];
        obstacle = JSONObjstacleFactory::create(mapItem);
        if (_obstacles == NULL) { _obstacles = new CCArray(); }
        _obstacles->addObject(obstacle);
        if (std::strcmp(obstacle->getType(), Obstacle::TESLA) == 0)
        {
            _teslaInteraction->addTeslaItem((TeslaItem*) obstacle);
        }
        _mapLayer->addChild(obstacle);
    }
}

void ObstaclesController::createFromTMX(cocos2d::CCTMXTiledMap *tileMap)
{
    CCArray* objectGroups = tileMap->getObjectGroups();
    
    CCObject* item;
    CCTMXObjectGroup* objectGroup;
    CCARRAY_FOREACH(objectGroups, item)
    {
        objectGroup = (CCTMXObjectGroup*) item;
        
        CCLog("hzhz");
    }
}