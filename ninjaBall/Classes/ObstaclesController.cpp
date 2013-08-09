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
    CCRect objectRect = CCRectMake(
            object->getPosition().x - object->getContentSize().width/4,
            object->getPosition().y - object->getContentSize().height/4,
            object->getContentSize().width/2,
            object->getContentSize().height/2);
    
    CCObject* item;
    CCSprite* obstacle;
    CCRect obstacleRect;
    CCARRAY_FOREACH(_obstacles, item)
    {
        obstacle = (CCSprite*) item;
        obstacleRect = CCRectMake(
            obstacle->getPosition().x - obstacle->getContentSize().width/4,
            obstacle->getPosition().y - obstacle->getContentSize().height/4,
            obstacle->getContentSize().width/2,
            obstacle->getContentSize().height/2);
        if (objectRect.intersectsRect(obstacleRect))
        {
            return true;
        }
    }
    return false;
}

void ObstaclesController::createRandomObstacles()
{
    int obstaclesNum = arc4random() % 3 + 2;
    char* sImageNumber;
    char* imagePath;
    int imageNumber;
    float imageX, imageY;
    Obstacle* obstacle;
    for (int i = 0; i < obstaclesNum; ++i) {
        imageNumber = arc4random() % MONSTERS_NUM;
        sImageNumber = new char[((sizeof (imageNumber + 1) * CHAR_BIT) + 2)/3 + 2];
        sprintf(sImageNumber, "%d", imageNumber + 1);
        imagePath = strcat(sImageNumber, ".png");
        
        obstacle = Obstacle::create();
        obstacle->initWithFile(imagePath);
        obstacle->setScale(0.5f);
        
        imageX = (arc4random() % (int)(Settings::VIRTUAL_WIDTH - obstacle->getContentSize().width)) +
                                        obstacle->getContentSize().width/2;
        imageY = (arc4random() % (int)(Settings::VIRTUAL_HEIGHT - obstacle->getContentSize().height)) +
                                        obstacle->getContentSize().height/2;
        obstacle->setPosition(ccp(imageX, imageY));
        
        obstacle->setLinearMoving(ccp(arc4random() % (int) Settings::VIRTUAL_WIDTH,
                                      arc4random() % (int) Settings::VIRTUAL_HEIGHT),
                                  ccp(arc4random() % (int) Settings::VIRTUAL_WIDTH,
                                      arc4random() % (int) Settings::VIRTUAL_HEIGHT));
        
        if (_obstacles == NULL) { _obstacles = new CCArray(); }
        _obstacles->addObject(obstacle);
        _mapLayer->addChild(obstacle);
    }
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