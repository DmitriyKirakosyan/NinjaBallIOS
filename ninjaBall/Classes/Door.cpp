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

Door::Door(const int id):Obstacle(id)
{
    _opened = false;

    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    this->initWithSpriteFrameName("door1.png");
   
    CCArray* animFrames = CCArray::createWithCapacity(10);
    
    char str[100] = {0};
    for (int i = 0; i < 10; ++i) {
        sprintf(str, "door%d.png", i+1);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames);
    animation->setDelayPerUnit(1 / 10.0f);
    _animate = CCAnimate::create(animation);
    _animate->retain();
}



void Door::on()
{
    _opened = true;
    this->stopAllActions();
    this->runAction(_animate);
}

void Door::off()
{
    _opened = false;
    this->stopAllActions();
    this->runAction(_animate->reverse());
}

bool Door::checkHit(cocos2d::CCSprite *object)
{
    return Obstacle::checkHit(object);
}