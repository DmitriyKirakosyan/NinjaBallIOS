//
//  Obstacle.h
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#ifndef __ninjaBall__Obstacle__
#define __ninjaBall__Obstacle__

#include "cocos2d.h"

class Obstacle : public cocos2d::CCSprite
{
public:
    Obstacle()
    {
        _movingPath = NULL;
        _isMoving = false;
        _currentTargetPoint = cocos2d::CCPointZero;
    }
    
    Obstacle(const char* fileName, const cocos2d::CCPoint position);
    Obstacle(const char* behaviour);

    void setLinearMoving(cocos2d::CCPoint point1, cocos2d::CCPoint point2);

    void stop();
    
    CREATE_FUNC(Obstacle);
    
private:
    
    
    
    void moveToPoint(cocos2d::CCPoint point);
    
    void onMoveToPointComplete(cocos2d::CCNode* sender);
    
    bool _isMoving;
    cocos2d::CCArray* _movingPath;
    cocos2d::CCPoint _currentTargetPoint;
    
};

#endif /* defined(__ninjaBall__Obstacle__) */
