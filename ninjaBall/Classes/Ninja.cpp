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
    if (_walkingPoints == NULL) { _walkingPoints = new std::vector<CCPoint*>(); }
    CCPoint* pPoint = new CCPoint();
    pPoint->x = point.x;
    pPoint->y = point.y;
    _walkingPoints->push_back(pPoint);
    if (!_isWalking)
    {
        this->goWalk();
    }
    
}

void Ninja::stopWalk()
{
    if (_walkingPoints != NULL)
    {
        while (_walkingPoints->size() > 0) _walkingPoints->pop_back();
        delete _walkingPoints;
        _walkingPoints = NULL;
    }
    _isWalking = false;
    this->stopAllActions();
}

void Ninja::goWalk()
{
    if (_walkingPoints == NULL || _walkingPoints->size() == 0)
    {
        CCLOGERROR("not enougth walking points!");
        return;
    }
    
    _isWalking = true;

    CCPoint* firstPoint = _walkingPoints->at(0);
    _currentWalkPoint = ccp(firstPoint->x, firstPoint->y);

    float rotateAngle = -90 - CC_RADIANS_TO_DEGREES(ccpToAngle(ccpSub(this->getPosition(), _currentWalkPoint)));
    
    
    this->runAction(CCRotateTo::create(.4, rotateAngle));
    //this->rotateTo(_currentWalkPoint.x, _currentWalkPoint.y);
    
	
    
    _walkingPoints->erase(_walkingPoints->begin());// removeObject(firstPoint);

    CCMoveTo* moveAction = CCMoveTo::create(.2, ccp(_currentWalkPoint.x, _currentWalkPoint.y));
    CCCallFuncN* callback = CCCallFuncN::create(_callbackTarget, _onMoveToPointCompleteFunc);
    CCFiniteTimeAction* action = CCSequence::create(moveAction, callback, NULL);
    this->runAction(action);
}

bool Ninja::canWalk()
{
    return _walkingPoints != NULL && _walkingPoints->size() > 0;
}