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

void Obstacle::moveToPoint(CCPoint point)
{
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