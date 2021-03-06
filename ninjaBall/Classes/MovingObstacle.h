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
    
    MovingObstacle(const int id);
    void setLinearMoving(cocos2d::CCPoint point1, cocos2d::CCPoint point2);
    
    void addMovePoint(cocos2d::CCPoint point);
    
    void stop();
    
private:
    void moveToPoint(cocos2d::CCPoint point);
    
    void onMoveToPointComplete(cocos2d::CCNode* sender);
    
    bool _isMoving;
    std::vector<cocos2d::CCPoint*>* _movingPath;
    cocos2d::CCPoint _currentTargetPoint;
    

};

#endif /* defined(__ninjaBall__MovingObstacle__) */
