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
#include "LevelProvider.h"
#include "ScreenHelper.h"

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

    CCSize screenSize = CCSize(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT);

    CCSprite* background = CCSprite::create("selectLevel.png");
    background->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    
    this->addChild(background);
    
    CCMenuItemImage *pCloseItem =
        CCMenuItemImage::create("CloseNormal.png",
                            "CloseSelected.png",
                            this, menu_selector(SelectLevelScene::closeCallback) );
    
    CCSize btnSize = pCloseItem->getContentSize();
    
    pCloseItem->setPosition( ccp(screenSize.width - btnSize.width/2,
                                 screenSize.height/2 - btnSize.height));
    
    // create menu, it's an autorelease object
    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, NULL);

    _levelBtns = new CCArray();
    int offset = 106;
    CCPoint position;
    
    CCMenuItemImage* levelBtn;
    int levelsNum = LevelProvider::getInstance()->LEVELS_NUM;
    for (int i = 0; i < levelsNum; ++i) {
        levelBtn = CCMenuItemImage::create("levelItem.png", "levelItem.png", "levelItemLocked.png",
                                           this, menu_selector(SelectLevelScene::levelSelectCallback));
        position = ccp(350 + i * offset, screenSize.height - (150 + ((int)(i / 5))* offset));
        levelBtn->setPosition(position);
        levelBtn->setScale(1.5f);
        if (i >= LevelProvider::getInstance()->getAvailableLevelsNum()) levelBtn->setEnabled(false);
        pMenu->addChild(levelBtn);
        _levelBtns->addObject(levelBtn);
    }
    
    
    pMenu->setPosition( cocos2d::CCPointZero );
    this->addChild(pMenu, 1);
 
    return true;
}

void SelectLevelScene::closeCallback(cocos2d::CCObject *pSender)
{
    CCScene* scene = MainScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void SelectLevelScene::levelSelectCallback(cocos2d::CCObject *pSender)
{
    
    int levelIndex = _levelBtns->indexOfObject(pSender);
    const char* levelName = LevelProvider::getInstance()->LEVELS[levelIndex];
    CCScene* scene = GameScene::create(levelName);
    CCDirector::sharedDirector()->replaceScene(scene);
}