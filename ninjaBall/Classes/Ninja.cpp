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
        CCObject* item;
        CCARRAY_FOREACH(_walkingPoints, item)
        {
            delete item;
        }
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
    _walkingPoints->removeObject(firstPoint);
    
    _currentWalkPoint = ccp(firstPoint->x, firstPoint->y);
	
    CCMoveTo* moveAction = CCMoveTo::create(1, ccp(firstPoint->x, firstPoint->y));
    CCCallFuncN* callback = CCCallFuncN::create(_callbackTarget, _onMoveToPointCompleteFunc);
    
    CCFiniteTimeAction* action = CCSequence::create(moveAction, callback, NULL);
    this->runAction(action);
}

bool Ninja::canWalk()
{
    return _walkingPoints != NULL && _walkingPoints->count() > 0;
}