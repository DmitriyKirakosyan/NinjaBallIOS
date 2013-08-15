//
//  MovingObstacle.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#include "MovingObstacle.h"

using namespace cocos2d;

MovingObstacle::MovingObstacle(const int id):Obstacle(id)
{
    _movingPath = NULL;
    _isMoving = false;
    _currentTargetPoint = CCPointZero;
    CCSprite::initWithFile(Obstacle::SAW_BKG_IMG);
    cocos2d::CCSprite* rotatedElement = CCSprite::create(Obstacle::SAW_IMG);
    rotatedElement->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    rotatedElement->runAction(CCRepeatForever::create(CCRotateBy::create(1, 180)));
    this->addChild(rotatedElement);
}


void MovingObstacle::stop()
{
    this->stopAllActions();
    _currentTargetPoint = CCPointZero;
}


//private

void MovingObstacle::setLinearMoving(CCPoint point1, CCPoint point2)
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

void MovingObstacle::addMovePoint(CCPoint point)
{
    if (_movingPath == NULL) { _movingPath = new CCArray(); }
    CCPoint* pPoint = new CCPoint();
    pPoint->x = point.x;
    pPoint->y = point.y;
    pPoint->autorelease();
    _movingPath->addObject(pPoint);
    if (!_isMoving) { this->moveToPoint(point); }
}

void MovingObstacle::moveToPoint(CCPoint point)
{
    _isMoving = true;
    _currentTargetPoint = point;
    float duration = (1.0/60) * ccpDistance(this->getPosition(), point);
    CCMoveTo* moveAction = CCMoveTo::create(duration, ccp(point.x, point.y));
    CCCallFuncN* callback = CCCallFuncN::create(this, callfuncN_selector(MovingObstacle::onMoveToPointComplete));
    CCFiniteTimeAction* action = CCSequence::create(moveAction, callback, NULL);
    this->runAction(action);
}

void MovingObstacle::onMoveToPointComplete(CCNode* sender)
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

