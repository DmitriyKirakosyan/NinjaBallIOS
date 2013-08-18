//
//  TeslaSpark.h
//  ninjaBall
//
//  Created by Dmitriy on 8/18/13.
//
//

#ifndef __ninjaBall__TeslaSpark__
#define __ninjaBall__TeslaSpark__

#include "cocos2d.h"

class TeslaItem;

class TeslaSpark : public cocos2d::CCSprite
{
public:
    TeslaSpark(TeslaItem* teslaItem1, TeslaItem* teslaItem2);
    void update();
    
    bool checkHit(cocos2d::CCSprite* object);
    
private:
    TeslaItem* _teslaItem1;
    TeslaItem* _teslaItem2;
};

#endif /* defined(__ninjaBall__TeslaSpark__) */
