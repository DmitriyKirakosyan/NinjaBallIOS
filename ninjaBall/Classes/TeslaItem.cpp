//
//  TeslaItem.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/17/13.
//
//

#include "TeslaItem.h"
#include "Ninja.h"
#include "Obstacle.h"

using namespace cocos2d;

TeslaItem::TeslaItem(const int id, const int friendId)
:MovingObstacle(id),
_friendId(friendId)
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    this->initWithSpriteFrameName("teslaItem1.png");
    
    CCArray* animFrames = CCArray::createWithCapacity(10);
    
    char str[100] = {0};
    for (int i = 0; i < 30; ++i) {
        int animNumber = i < 15 ? i + 1 : 30 - i;
        sprintf(str, "teslaItem%d.png", animNumber);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames);
    animation->setDelayPerUnit(1 / 30.0f);
    CCAnimate* animate = CCAnimate::create(animation);
    this->runAction(CCRepeatForever::create(animate));
}

TeslaItem::~TeslaItem()
{
    this->stopAllActions();
}

bool TeslaItem::checkHeroDamage(Ninja *ninja)
{
    return Obstacle::checkHit(ninja);
}