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

class Door : public Obstacle, public IDoor
{
public:
    Door()
    {
        cocos2d::CCSprite::initWithFile(Obstacle::YELLOW_MONSTER_IMG);
        _opened = false;
    }
    
    void open();
    void close();
    
    
private:
    bool _opened;
    
};

#endif /* defined(__ninjaBall__Door__) */
