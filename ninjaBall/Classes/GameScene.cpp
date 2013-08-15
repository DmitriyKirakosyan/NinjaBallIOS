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
#include "Settings.h"
#include "ScreenHelper.h"
#include "MainScene.h"
#include "LevelProvider.h"

using namespace cocos2d;

GameScene* GameScene::create(const char *levelName)
{
    GameScene *pRet = new GameScene();
    if (pRet && pRet->init(levelName))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }

}

bool GameScene::init(const char* levelName)
{
    if (CCScene::init())
    {
        this->setAnchorPoint(ccp(0, 0));
        this->setScale(Settings::density);
        this->setPosition(ccp(Settings::REAL_WIDTH_OFFSET, Settings::REAL_HEIGHT_OFFSET));
        GameSceneLayer* layer = new GameSceneLayer();
        layer->initWithColor(ccc4(255, 255, 255, 255));
        layer->setContentSize(CCSize(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT));
        
        CCLog("position : %f, %f", layer->getPosition().x, layer->getPosition().y);
        
        layer->start(levelName);
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

void GameSceneLayer::start(const char* levelName)
{
    
    _isDrawing = false;
    _touchPoints = NULL;
    this->setTouchEnabled(true);

    float backScaleX = Settings::FULL_VIRTUAL_WIDTH / Settings::VIRTUAL_WIDTH;
    float backScaleY = Settings::FULL_VIRTUAL_HEIGHT / Settings::VIRTUAL_HEIGHT;
    
    CCSprite* back = CCSprite::create("storeHouseBkg.png");
    back->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    back->setScaleX(backScaleX);
    back->setScaleY(backScaleY);
    this->addChild(back);
    
    _ninja = new Ninja(callfuncN_selector(GameSceneLayer::onNinjaMoveToPointComplete), this);
    _ninja->initWithFile("ninja.png");

    _windowManager = new WindowManager(this, new GameWindowFactory(this));
    _drawingController = new DrawingController(this);
    _mapView = new MapView(_ninja);
    this->addChild(_mapView);
    this->addChild(_ninja, 1);
    
    this->startLevel(levelName);
}

void GameSceneLayer::startLevel(const char* levelName)
{
    _currentLevelName = levelName;
    _mapView->createLevel(levelName);
    this->schedule(schedule_selector(GameSceneLayer::update));
}


void GameSceneLayer::nextLevel()
{
    if (LevelProvider::getInstance()->hasNextLevel(_currentLevelName.c_str()))
    {
        this->startLevel(LevelProvider::getInstance()->getNextLevel(_currentLevelName.c_str()));
    }
}

bool GameSceneLayer::canStartNextLevel()
{
    if (LevelProvider::getInstance()->hasNextLevel(_currentLevelName.c_str()))
    {
        const char* nextLevel = LevelProvider::getInstance()->getNextLevel(_currentLevelName.c_str());
        if (LevelProvider::getInstance()->isLevelAvailable(nextLevel)) {
            return true;
        }
    }
    return false;
}

void GameSceneLayer::replyLevel()
{
    this->startLevel(_currentLevelName.c_str());
}

void GameSceneLayer::returnToMainMenu()
{
    CCScene* mainScene = MainScene::scene();
    CCDirector::sharedDirector()->replaceScene(mainScene);
}

void GameSceneLayer::update(float dt)
{
    if (_mapView->getObstaclesController()->testDamage(_ninja))
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
    _mapView->tick();
    if (_mapView->isNinjaWin(_ninja))
    {
        //show win level window;
        _ninja->stopWalk();
        _drawingController->clear();
        _mapView->clear();
        this->unschedule(schedule_selector(GameSceneLayer::update));
        LevelProvider::getInstance()->completeLevel(_currentLevelName.c_str());
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
    location = ScreenHelper::convetGLtoVirtual(location);
    if (location.x < 0 || location.x > Settings::VIRTUAL_WIDTH ||
        location.y < 0 || location.y > Settings::VIRTUAL_HEIGHT) {
        return;
    }
    
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
    CCTouch* touch = (CCTouch*) touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    location = ScreenHelper::convetGLtoVirtual(location);
    if (location.x < 0 || location.x > Settings::VIRTUAL_WIDTH ||
        location.y < 0 || location.y > Settings::VIRTUAL_HEIGHT) {
        return;
    }
    if (_isDrawing)
    {
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
