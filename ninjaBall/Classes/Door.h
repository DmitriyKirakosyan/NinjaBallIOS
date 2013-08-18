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
    Door(const int id);
    ~Door();
    //switchable
    void on();
    void off();
    inline bool isOn() { return _opened; }
    
    const char* getType() { return Obstacle::DOOR; }
    
    bool checkHit(cocos2d::CCSprite* object);
    inline bool checkHeroDamage(Ninja* ninja) { return false; }
    
    
private:
    bool _opened;
    
    cocos2d::CCAnimate* _animate;
    
};

#endif /* defined(__ninjaBall__Door__) */
