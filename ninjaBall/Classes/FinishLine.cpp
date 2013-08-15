//
//  FinishLine.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/15/13.
//
//

#include "FinishLine.h"


using namespace cocos2d;

bool FinishLine::init()
{

    if (!CCSprite::init()) return false;
    
    this->initWithFile("finish.png");
        
    CCSprite* leftBall = CCSprite::create("finishLight.png");
    CCSprite* rightBall = CCSprite::create("finishLight.png");
    leftBall->setPosition(ccp(leftBall->getContentSize().width/2-5,
                              leftBall->getContentSize().height/2-5));
    rightBall->setPosition(ccp(this->getContentSize().width - rightBall->getContentSize().width/2 + 5,
                               rightBall->getContentSize().height/2 - 5));
    this->addChild(leftBall);
    this->addChild(rightBall);
    leftBall->runAction(CCRepeatForever::create(CCRotateBy::create(1, 180)));
    rightBall->runAction(CCRepeatForever::create(CCRotateBy::create(1, 180)));
    
    //TODO debug
    this->setScale(1.5);
    
    return true;
}