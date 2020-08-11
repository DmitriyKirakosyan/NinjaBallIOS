//
//  MovingSaw.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/17/13.
//
//

#include "MovingSaw.h"
#include "Ninja.h"

using namespace cocos2d;

MovingSaw::MovingSaw(const int id):MovingObstacle(id)
{
    CCSprite::initWithFile(Obstacle::SAW_BKG_IMG);
    cocos2d::CCSprite* rotatedElement = CCSprite::create(Obstacle::SAW_IMG);
    rotatedElement->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    rotatedElement->runAction(CCRepeatForever::create(CCRotateBy::create(1, 180)));
    this->addChild(rotatedElement);
}

bool MovingSaw::checkHeroDamage(Ninja *ninja)
{
    return Obstacle::checkHit(ninja);
}