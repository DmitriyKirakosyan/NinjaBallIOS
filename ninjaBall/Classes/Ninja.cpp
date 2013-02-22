//
//  Ninja.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/17/13.
//
//

#include "Ninja.h"

using namespace cocos2d;

void Ninja::addWalkingPoint(CCPoint point)
{
    if (_walkingPoints == NULL) { _walkingPoints = new CCArray(); }
    CCPoint* pPoint = new CCPoint();
    pPoint->x = point.x;
    pPoint->y = point.y;
    pPoint->autorelease();
    _walkingPoints->addObject(pPoint);
    if (!_isWalking)
    {
        this->goWalk();
    }
}

void Ninja::stopWalk()
{
    if (_walkingPoints != NULL)
    {
        _walkingPoints->removeAllObjects();
    }
    _isWalking = false;
    this->stopAllActions();
}

void Ninja::goWalk()
{
    if (_walkingPoints == NULL || _walkingPoints->count() == 0)
    {
        CCLOGERROR("not enougth walking points!");
        return;
    }
    
    _isWalking = true;

    CCPoint* firstPoint = (CCPoint*) _walkingPoints->objectAtIndex(0);
    _currentWalkPoint = ccp(firstPoint->x, firstPoint->y);
	
    _walkingPoints->removeObject(firstPoint);

    CCMoveTo* moveAction = CCMoveTo::create(.5, ccp(_currentWalkPoint.x, _currentWalkPoint.y));
    CCCallFuncN* callback = CCCallFuncN::create(_callbackTarget, _onMoveToPointCompleteFunc);
    CCFiniteTimeAction* action = CCSequence::create(moveAction, callback, NULL);
    this->runAction(action);
}

bool Ninja::canWalk()
{
    return _walkingPoints != NULL && _walkingPoints->count() > 0;
}