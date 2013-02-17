//
//  Ninja.h
//  ninjaBall
//
//  Created by Dmitriy on 2/17/13.
//
//

#ifndef __ninjaBall__Ninja__
#define __ninjaBall__Ninja__

#include "cocos2d.h"

class Ninja : public cocos2d::CCSprite
{
public:
    Ninja(cocos2d::SEL_CallFuncN onMoveToPointCompleteFunc, CCObject* callbackTarget)
    {
        _isWalking = false;
        _walkingPoints = NULL;
        
        if (onMoveToPointCompleteFunc == NULL)
        {
            CCLOGERROR("bad arg");
        }
        _onMoveToPointCompleteFunc = onMoveToPointCompleteFunc;
        _callbackTarget = callbackTarget;
    }
    
    void addWalkingPoint(cocos2d::CCPoint point);
    void stopWalk();
    void goWalk();
    bool canWalk();
    
    inline cocos2d::CCPoint getCurrentWalkPoint()
    {
        return _currentWalkPoint;
    }
    
private:
    bool _isWalking;
    
    cocos2d::CCArray* _walkingPoints;
    
    cocos2d::CCPoint _currentWalkPoint;
    
    cocos2d::SEL_CallFuncN _onMoveToPointCompleteFunc;
    cocos2d::CCObject* _callbackTarget;
    
    void onMoveToPointComplete(cocos2d::CCNode* sender);
    
};

#endif /* defined(__ninjaBall__Ninja__) */
