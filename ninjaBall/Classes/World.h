//
//  World.h
//  ninjaBall
//
//  Created by Dmitriy on 8/14/13.
//
//

#ifndef ninjaBall_World_h
#define ninjaBall_World_h

#include "cocos2d.h"

class Ninja;

class World
{
public:
    Ninja* ninja;
    cocos2d::CCArray* obstacles;
};

#endif
