//
//  MovingObstacle.h
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#ifndef __ninjaBall__MovingObstacle__
#define __ninjaBall__MovingObstacle__

#include <iostream>
#include "Obstacle.h"

class MovingObstacle : public Obstacle
{
public:
    
    MovingObstacle(const int id):Obstacle(id)
    {
        _movingPath = NULL;
        _isMoving = false;
        _currentTargetPoint = cocos2d::CCPointZero;
        cocos2d::CCSprite::initWithFile(Obstacle::RABBIT_MONSTER_IMG);
    }
    
    void setLinearMoving(cocos2d::CCPoint point1, cocos2d::CCPoint point2);
    
    void addMovePoint(cocos2d::CCPoint point);
    
    void stop();
    
private:
    void moveToPoint(cocos2d::CCPoint point);
    
    void onMoveToPointComplete(cocos2d::CCNode* sender);
    
    bool _isMoving;
    cocos2d::CCArray* _movingPath;
    cocos2d::CCPoint _currentTargetPoint;
    

};

#endif /* defined(__ninjaBall__MovingObstacle__) */
