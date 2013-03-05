//
//  GameScene.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/13/13.
//
//

#include "GameScene.h"
#include "DrawingController.h"
#include "Ninja.h"
#include "MapView.h"
#include "ObstaclesController.h"
#include "GameWindowFactory.h"
#include "WindowManager.h"

using namespace cocos2d;

bool GameScene::init()
{
    if (CCScene::init())
    {
        GameSceneLayer* layer = new GameSceneLayer();
        layer->initWithColor(ccc4(255, 255, 255, 255));
        layer->start();
        this->addChild(layer);
        this->addChild(layer->getWindowLayer());
        return true;
    }
    return false;
}

//GameSceneLayer

CCLayer* GameSceneLayer::getWindowLayer()
{
    return _windowManager;
}

void GameSceneLayer::start()
{
    _isDrawing = false;
    _touchPoints = NULL;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);

    _ninja = new Ninja(callfuncN_selector(GameSceneLayer::onNinjaMoveToPointComplete), this);
    _ninja->initWithFile("ninja.png");

    _windowManager = new WindowManager(this, new GameWindowFactory(this));
    _drawingController = new DrawingController(this);
    _mapView = new MapView(winSize, _ninja);
    this->addChild(_mapView);
    this->addChild(_ninja, 1);
    this->startLevel();
}

void GameSceneLayer::startLevel()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _mapView->createLevel("test_map.json");
//    _ninja->setPosition(ccp(winSize.width - _ninja->getContentSize().width/2,
//                            _ninja->getContentSize().height/2));
    this->schedule(schedule_selector(GameSceneLayer::update));
}

void GameSceneLayer::nextLevel()
{
    this->startLevel();
}

void GameSceneLayer::replyLevel()
{
    this->startLevel();
}

void GameSceneLayer::returnToMainMenu()
{
    
}

void GameSceneLayer::update()
{
    if (_mapView->getObstacles()->testHit(_ninja))
    {
        if (_ninja->getOpacity() == 255)
        {
            _ninja->setOpacity(100);
        }
    }
    else
    {
        if (_ninja->getOpacity() != 255)
        {
            _ninja->setOpacity(255);
        }
    }
    if (_mapView->isNinjaWin(_ninja))
    {
        //show win level window;
        _ninja->stopWalk();
        _drawingController->clear();
        _mapView->clear();
        this->unschedule(schedule_selector(GameSceneLayer::update));
        _windowManager->showWindow(GameWindowFactory::LEVEL_COMPLETE_WINDOW);
    }
}

//touch callbacks

void GameSceneLayer::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    _drawingController->clear();
    _ninja->stopWalk();

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
    _drawingController->stopDraw();
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
        CCArray* partPoints = _drawingController->drawPathToPoint(location);
        if (partPoints != NULL && partPoints->count() > 0)
        {
            CCObject* item;
            CCARRAY_FOREACH(partPoints, item)
            {
                _ninja->addWalkingPoint(ccp( ((CCPoint*)item)->x, ((CCPoint*)item)->y));
            }
            partPoints->removeAllObjects();
        }
        
    }
}

void GameSceneLayer::onNinjaMoveToPointComplete(CCNode* sender)
{
    _drawingController->removePathPartByPointFromScreen(_ninja->getCurrentWalkPoint());
    if (_ninja->canWalk())
    {
        _ninja->goWalk();
    }
    else
    {
        _ninja->stopWalk();
    }
}
