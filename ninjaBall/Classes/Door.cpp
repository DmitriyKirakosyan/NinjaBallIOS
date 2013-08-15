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
    //cocos2d::CCSprite::initWithFile(Obstacle::MAULBALL_IMG);
    
    _opened = false;
    
    //CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("doorAnim.png");

    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("doorAnim.plist");
    
    this->initWithSpriteFrameName("door1.png");
    //this->setBatchNode(spritebatch);
   
//    spritebatch->addChild(this);
//    CCSprite* childSprite = CCSprite::createWithSpriteFrameName("door1.png");
//
//    this->addChild(spritebatch);

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