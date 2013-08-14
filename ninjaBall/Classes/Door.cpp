//
//  Door.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#include "Door.h"
#include "World.h"
#include "Ninja.h"

using namespace cocos2d;


void Door::on()
{
    _opened = true;
    this->setScale(1.5);
}

void Door::off()
{
    _opened = false;
    this->setScale(1);
}

bool Door::checkHit(cocos2d::CCSprite *object)
{
    return Obstacle::checkHit(object);
}