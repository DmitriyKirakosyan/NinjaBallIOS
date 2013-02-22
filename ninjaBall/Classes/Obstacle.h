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
    Obstacle() {}
    Obstacle(const char* fileName, const cocos2d::CCPoint position);
    Obstacle(const char* behaviour);
    
private:
    
};

#endif /* defined(__ninjaBall__Obstacle__) */
