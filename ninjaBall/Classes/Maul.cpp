//
//  Maul.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/15/13.
//
//

#include "Maul.h"
#include "Ninja.h"

using namespace cocos2d;

Maul::Maul(const int id, float rotationSpeed):
Obstacle(id),
_rotationSpeed(rotationSpeed)
{
    this->initWithFile("maulBase.png");
    
    CCSprite* rope = CCSprite::create("maulRope.png");
    CCSprite* ball = CCSprite::create("maulBall.png");
    rope->setPosition(ccp(this->getContentSize().width/2,
                      this->getContentSize().height/2 - rope->getContentSize().height/2));
    ball->setPosition(ccp(this->getContentSize().width/2,
                          this->getContentSize().height/2 - rope->getContentSize().height));
    
    this->addChild(rope);
    this->addChild(ball);
    ball->runAction(CCRepeatForever::create(CCRotateBy::create(1, 180)));
    this->runAction(CCRepeatForever::create(CCRotateBy::create(_rotationSpeed, 180)));
    
    _damageRect = ball->getTextureRect();
    _radiusToDamageRect = rope->getContentSize().height;
}

bool Maul::checkHeroDamage(Ninja *ninja)
{
    float rotation = this->getRotation();
    //-180 coz maul looking at bottom
    float damagePointX = sin((rotation-180) / 180 * 3.14);
    float damagePointY = cos((rotation-180) / 180 * 3.14);
    
    CCRect baseRect = this->getTextureRect();
    float baseX = this->getPosition().x - _damageRect.size.width/2;
    float baseY = this->getPosition().y - _damageRect.size.height/2;
    damagePointX = baseX + damagePointX * _radiusToDamageRect;
    damagePointY = baseY + damagePointY * _radiusToDamageRect;
    _damageRect.origin = ccp(damagePointX, damagePointY);
    

    CCRect ninjaRect = ninja->getTextureRect();
    ninjaRect.origin = ccp(ninja->getPosition().x - ninja->getContentSize().width/2,
                            ninja->getPosition().y - ninja->getContentSize().height/2);
    
    return ninjaRect.intersectsRect(_damageRect);
}