//
//  TeslaItem.h
//  ninjaBall
//
//  Created by Dmitriy on 8/17/13.
//
//

#ifndef __ninjaBall__TeslaItem__
#define __ninjaBall__TeslaItem__

#include "MovingObstacle.h"

class TeslaItem : public MovingObstacle
{
public:
    TeslaItem(const int id, const int friendId);
    ~TeslaItem();
    
    inline bool checkHit(cocos2d::CCSprite* object) { return false; }
    bool checkHeroDamage(Ninja* ninja);
    
    inline int getFriendId() { return _friendId; }

private:
    int _friendId;

};

#endif /* defined(__ninjaBall__TeslaItem__) */
