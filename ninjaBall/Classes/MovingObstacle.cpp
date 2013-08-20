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
        _movingPath = new std::vector<CCPoint*>();
        pPoint = new CCPoint();
        pPoint->x = point1.x;
        pPoint->y = point1.y;
        _movingPath->push_back(pPoint);//addObject(pPoint);
        pPoint = new CCPoint();
        pPoint->x = point2.x;
        pPoint->y = point2.y;
        _movingPath->push_back(pPoint);
        
        //TODO memory leak here. need to release pPoint after use
        
        if (!_isMoving) { this->moveToPoint(point1); }
    }
    else
    {
        //remove and create, for example;
    }
}

void MovingObstacle::addMovePoint(CCPoint point)
{
    if (_movingPath == NULL) { _movingPath = new std::vector<CCPoint*>(); }
    CCPoint* pPoint = new CCPoint();
    pPoint->x = point.x;
    pPoint->y = point.y;
    _movingPath->push_back(pPoint);
    if (!_isMoving) { this->moveToPoint(point); }
    
    //TODO memory leaks with point
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
    
    CCPoint* pPoint;
    if (_movingPath != NULL && _movingPath->size() > 0)
    {
        for (int i = 0; i < _movingPath->size(); ++i) {
            pPoint = _movingPath->at(i);
            if (_currentTargetPoint.x == pPoint->x && _currentTargetPoint.y == pPoint->y)
            {
                const unsigned int nextIndex = (i < _movingPath->size()-1) ? i + 1 : 0;
                pPoint = _movingPath->at(nextIndex);
                moveToPoint(ccp(pPoint->x, pPoint->y));
                movingContinue = true;
                break;
            }
           
        }
    }
    if (!movingContinue) { _isMoving = false; }
}

