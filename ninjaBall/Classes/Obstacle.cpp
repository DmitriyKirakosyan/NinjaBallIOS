//
//  Obstacle.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#include "Obstacle.h"
#include "Settings.h"

using namespace cocos2d;

const char* Obstacle::WALKING_WALL = "walking_wall";

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

Obstacle* Obstacle::createFromJSON(Json::Value obstacleJson)
{
    Obstacle* result = new Obstacle();

    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float itemX = obstacleJson.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float itemY = obstacleJson.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    
    CCLog("type of monster char* : %s", obstacleJson.get("type", "").asCString());
    CCLog("type of monster std::string : %s", obstacleJson.get("type", "").asString().c_str());
    
    
    std::string type = obstacleJson.get("type", "").asCString();
    CCLog("var type : %s", type.c_str());
    result->initWithFile(Obstacle::getMonsterImage(type.c_str()));
    result->setScale(0.5f);
    result->setPosition(ccp(itemX, itemY));
    
    if (std::strcmp(type.c_str(), WALKING_WALL) == 0)
    {
        Json::Value walkPath = obstacleJson.get("walk_path", "");
        for (int i = 0; i < walkPath.size(); ++i) {
            result->addMovePoint(ccp(walkPath[i].get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                     walkPath[i].get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
        }
    }
    
    result->autorelease();
    return result;
}

void Obstacle::stop()
{
    this->stopAllActions();
    _currentTargetPoint = CCPointZero;
}


//private

void Obstacle::setLinearMoving(CCPoint point1, CCPoint point2)
{
    CCPoint* pPoint;
    if (_movingPath == NULL)
    {
        _movingPath = new CCArray();
        pPoint = new CCPoint();
        pPoint->x = point1.x;
        pPoint->y = point1.y;
        pPoint->autorelease();
        _movingPath->addObject(pPoint);
        pPoint = new CCPoint();
        pPoint->x = point2.x;
        pPoint->y = point2.y;
        pPoint->autorelease();
        _movingPath->addObject(pPoint);
        
        if (!_isMoving) { this->moveToPoint(point1); }
    }
    else
    {
        //remove and create, for example;
    }
}

void Obstacle::addMovePoint(CCPoint point)
{
    if (_movingPath == NULL) { _movingPath = new CCArray(); }
    CCPoint* pPoint = new CCPoint();
    pPoint->x = point.x;
    pPoint->y = point.y;
    pPoint->autorelease();
    _movingPath->addObject(pPoint);
    if (!_isMoving) { this->moveToPoint(point); }
}

void Obstacle::moveToPoint(CCPoint point)
{
    _isMoving = true;
    _currentTargetPoint = point;
    float duration = (1.0/60) * ccpDistance(this->getPosition(), point);
    CCMoveTo* moveAction = CCMoveTo::create(duration, ccp(point.x, point.y));
    CCCallFuncN* callback = CCCallFuncN::create(this, callfuncN_selector(Obstacle::onMoveToPointComplete));
    CCFiniteTimeAction* action = CCSequence::create(moveAction, callback, NULL);
    this->runAction(action);
}

void Obstacle::onMoveToPointComplete(CCNode* sender)
{
    bool movingContinue = false;
    if (_movingPath != NULL && _movingPath->count() > 0)
    {
        CCObject* item;
        CCPoint* pPoint;
        CCARRAY_FOREACH(_movingPath, item)
        {
            pPoint = (CCPoint*) item;
            if (_currentTargetPoint.x == pPoint->x && _currentTargetPoint.y == pPoint->y)
            {
                const unsigned int index = _movingPath->indexOfObject(item);
                const unsigned int nextIndex = (index < _movingPath->count()-1) ? index + 1 : 0;
                pPoint = (CCPoint*) _movingPath->objectAtIndex(nextIndex);
                moveToPoint(ccp(pPoint->x, pPoint->y));
                movingContinue = true;
                break;
            }
        }
    }
    if (!movingContinue) { _isMoving = false; }
}

const char* Obstacle::getMonsterImage(const char* monsterType)
{
    CCLog("strings : %s, %s", monsterType, WALKING_WALL);
    const char* result;
    if (std::strcmp(monsterType, WALKING_WALL) == 0) {
        result = "yellowMonster.png";
    }
    else
    {
        CCLOGERROR("unknown monster type");
        result = "yellowMonster.png";
    }
    CCLog("strings : %s, %s", monsterType, WALKING_WALL);
    return result;
}