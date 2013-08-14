//
//  Door.h
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#ifndef __ninjaBall__Door__
#define __ninjaBall__Door__

#include "Obstacle.h"
#include "IDoor.h"

class Door : public Obstacle
{
public:
    Door(const int id): Obstacle(id)
    {
        cocos2d::CCSprite::initWithFile(Obstacle::YELLOW_MONSTER_IMG);
        _opened = false;
    }
    
    //switchable
    void on();
    void off();
    inline bool isOn() { return _opened; }
    
    bool checkHit(cocos2d::CCSprite* object);
    inline bool checkHeroDamage(Ninja* ninja) { return false; }
    
    
private:
    bool _opened;
    
};

#endif /* defined(__ninjaBall__Door__) */
