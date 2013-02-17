//
//  GameScene.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/13/13.
//
//

#include "GameScene.h"
#include "DrawingController.h"

using namespace cocos2d;

bool GameScene::init()
{
    if (CCScene::init())
    {
        GameSceneLayer* layer = new GameSceneLayer();
        layer->initWithColor(ccc4(255, 255, 255, 255));
        
        layer->start();
        
        this->addChild(layer);
        
        return true;
    }
    
    return false;
}

//GameSceneLayer

void GameSceneLayer::start()
{
    _isDrawing = false;
    _touchPoints = NULL;
    
    this->setTouchEnabled(true);
    
    _drawingController = new DrawingController(this);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _ninja = new CCSprite();
    _ninja->initWithFile("ninja.png");
    _ninja->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    
    this->addChild(_ninja);
}

//touch callbacks

void GameSceneLayer::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch* touch = (CCTouch*) touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    CCPoint ninjaPoint = _ninja->getPosition();
    CCSize ninjaSize = _ninja->getContentSize();
    
    //if location under ninja
    if (location.x > ninjaPoint.x - ninjaSize.width/2 && location.x < ninjaPoint.x + ninjaSize.width/2 &&
        location.y > ninjaPoint.y - ninjaSize.height/2 && location.y < ninjaPoint.y + ninjaSize.height/2)
    {
        _drawingController->setStartPoint(location);
        _isDrawing = true;
    }
}

void GameSceneLayer::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _isDrawing = false;
    _drawingController->clear();
}

void GameSceneLayer::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    if (_isDrawing)
    {
        CCTouch* touch = (CCTouch*) touches->anyObject();
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        if (_touchPoints == NULL)
        {
            _touchPoints = new CCArray();
        }
        
        CCPoint* touchPoint = new CCPoint();
        touchPoint->setPoint(location.x, location.y);
        _touchPoints->addObject(touchPoint);
        
        _drawingController->drawPathToPoint(location);
    }
}
