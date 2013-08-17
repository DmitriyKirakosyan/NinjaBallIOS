//
//  MovingSaw.h
//  ninjaBall
//
//  Created by Dmitriy on 8/17/13.
//
//

#ifndef __ninjaBall__MovingSaw__
#define __ninjaBall__MovingSaw__

#include "MovingObstacle.h"

class Ninja; 

class MovingSaw : public MovingObstacle
{
public:
    MovingSaw(const int id);
    
    virtual inline bool checkHit(cocos2d::CCSprite* object) { return false; }
    
    virtual bool checkHeroDamage(Ninja* ninja);
};

#endif /* defined(__ninjaBall__MovingSaw__) */
