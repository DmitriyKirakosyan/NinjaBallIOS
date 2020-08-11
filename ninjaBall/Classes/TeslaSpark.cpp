//
//  TeslaSpark.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/18/13.
//
//

#include "TeslaSpark.h"
#include "TeslaItem.h"

using namespace cocos2d;

TeslaSpark::TeslaSpark(TeslaItem* teslaItem1, TeslaItem* teslaItem2):
_teslaItem1(teslaItem1),
_teslaItem2(teslaItem2)
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    this->initWithSpriteFrameName("sparks1.png");
    
    CCArray* animFrames = CCArray::createWithCapacity(10);
    
    char str[100] = {0};
    for (int i = 0; i < 3; ++i) {
        sprintf(str, "sparks%d.png", i+1);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames);
    animation->setDelayPerUnit(0.1 / 3.0f);
    CCAnimate* animate = CCAnimate::create(animation);
    this->runAction(CCRepeatForever::create(animate));
    
    this->update();
}



void TeslaSpark::update()
{
    CCPoint p1 = _teslaItem1->getPosition();
    CCPoint p2 = _teslaItem2->getPosition();
    
    float centerX = p1.x + 0.5 * (p2.x - p1.x);
    float centerY = p1.y + 0.5 * (p2.y - p1.y);
    
    float teslaDistance = ccpDistance(p1, p2);
    float scale = teslaDistance / this->getContentSize().width;
    this->setScaleX(scale);
    
    this->setPosition(ccp(centerX, centerY));
    
    float deltaX = p1.x - p2.x;
    float deltaY = p1.y - p2.y;
    float engle = -atan2f(deltaY, deltaX) * 180 / M_PI;
    this->setRotation(engle);
}

bool TeslaSpark::checkHit(CCSprite* object)
{
    float width = this->getContentSize().width * this->getScaleX();
    float height = this->getContentSize().height * this->getScaleY();
    CCRect selfRect = CCRect(this->getPosition().x - width/2,
                             this->getPosition().y - height/2,
                             width, height);
    CCPoint rotatedPoint = ccpRotateByAngle(object->getPosition(), this->getPosition(),
                                            CC_DEGREES_TO_RADIANS(this->getRotation()));
    CCRect objRect = object->getTextureRect();
    objRect.origin = ccp(rotatedPoint.x - object->getContentSize().width/2,
                         rotatedPoint.y - object->getContentSize().height/2);
    return objRect.intersectsRect(selfRect);
}