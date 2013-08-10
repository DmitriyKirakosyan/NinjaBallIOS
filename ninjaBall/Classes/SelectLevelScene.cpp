//
//  SelectLevelScene.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/8/13.
//
//

#include "SelectLevelScene.h"
#include "Settings.h"
#include "MainScene.h"
#include "GameScene.h"

using namespace cocos2d;
//using namespace CocosDenshion;


CCScene* SelectLevelScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    scene->setAnchorPoint(CCPointZero);
    scene->setContentSize(CCSize(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT));
    
    scene->setScale(Settings::density);
    scene->setPosition(ccp(Settings::REAL_WIDTH_OFFSET, Settings::REAL_HEIGHT_OFFSET));
    
    // 'layer' is an autorelease object
    SelectLevelScene *layer = SelectLevelScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool SelectLevelScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }


    CCSprite* background = CCSprite::create("selectLevel.png");
    background->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    
    this->addChild(background);
    
    CCMenuItemImage *pCloseItem =
        CCMenuItemImage::create("CloseNormal.png",
                            "CloseSelected.png",
                            this, menu_selector(SelectLevelScene::closeCallback) );
    
    CCSize btnSize = pCloseItem->getContentSize();
    
    pCloseItem->setPosition( ccp(Settings::VIRTUAL_WIDTH - btnSize.width/2,
                                 Settings::VIRTUAL_HEIGHT/2 - btnSize.height));
    
    CCMenuItemImage* pPlayItem =
    CCMenuItemImage::create("Start.png", "Start.png",
                            this, menu_selector(SelectLevelScene::playCallback));
    
    btnSize = pPlayItem->getContentSize();
    pPlayItem->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    
    // create menu, it's an autorelease object
    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, pPlayItem, NULL);
    pMenu->setPosition( cocos2d::CCPointZero );
    this->addChild(pMenu, 1);
 
    return true;
}

void SelectLevelScene::closeCallback(cocos2d::CCObject *pSender)
{
    CCScene* scene = MainScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void SelectLevelScene::playCallback(cocos2d::CCObject *pSender)
{
    CCScene* scene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}