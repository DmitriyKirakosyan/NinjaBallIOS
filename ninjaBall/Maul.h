//
//  Maul.h
//  ninjaBall
//
//  Created by Dmitriy on 8/15/13.
//
//

#ifndef __ninjaBall__Maul__
#define __ninjaBall__Maul__

#include "Obstacle.h"

class Ninja;

class Maul : public Obstacle
{
public:
    Maul(const int id, float rotationSpeed);
    
    inline bool checkHit(cocos2d::CCSprite* mapObject) { return false; }
    bool checkHeroDamage(Ninja* ninja);
    
private:
    float _rotationSpeed;
    float _radiusToDamageRect;
    cocos2d::CCRect _damageRect;
};

#endif /* defined(__ninjaBall__Maul__) */
