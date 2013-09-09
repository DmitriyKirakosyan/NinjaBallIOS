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
#include "InterfacePositions.h"

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
    
    
    float backScaleX = Settings::FULL_VIRTUAL_WIDTH / Settings::VIRTUAL_WIDTH;
    float backScaleY = Settings::FULL_VIRTUAL_HEIGHT / Settings::VIRTUAL_HEIGHT;
    
    
    CCSprite* imposedBkg = CCSprite::create("selectLevel/selLevImBkg.png");
    imposedBkg->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    imposedBkg->setScaleX(backScaleX);
    imposedBkg->setScaleY(backScaleY);

    CCSprite* selectMenuBkg = CCSprite::create("selectLevel/selMenuBkg.png");
    selectMenuBkg->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    selectMenuBkg->setScaleX(backScaleX);
    selectMenuBkg->setScaleY(backScaleY);
    
    CCSprite* rollCircle = CCSprite::create("selectLevel/selLevCircle.png");
    rollCircle->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    rollCircle->runAction(CCRepeatForever::create(CCRotateBy::create(1, 10)));
    
    CCSprite* selBkgLevel = CCSprite::create("selectLevel/selBkgLevel.png");
    selBkgLevel->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    
    this->addChild(selectMenuBkg);
    this->addChild(rollCircle);
    this->addChild(selBkgLevel);
    this->addChild(imposedBkg);
    
    CCMenuItemImage *pCloseItem =
        CCMenuItemImage::create("CloseNormal.png",
                            "CloseSelected.png",
                            this, menu_selector(SelectLevelScene::closeCallback) );
    
    CCSize btnSize = pCloseItem->getContentSize();
    
    pCloseItem->setPosition( ccp(screenSize.width - btnSize.width/2,
                                 screenSize.height - btnSize.height/2));
    
    // create menu, it's an autorelease object
    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, NULL);

    _levelBtns = new CCArray();
    
    int startX = 50;
    float itemY, itemX;
    
    float xOffset = (selBkgLevel->getContentSize().width - startX*2) / ITEMS_NUM_IN_RAW;
    
    CCMenuItemImage* levelBtn;
    int levelsNum = LevelProvider::getInstance()->LEVELS_NUM;
    for (int i = 0; i < levelsNum; ++i) {
        levelBtn = CCMenuItemImage::create("selectLevel/levelItem.png", "selectLevel/levelItem.png", "selectLevel/lockedLevelItem.png",
                                           this, menu_selector(SelectLevelScene::levelSelectCallback));
        itemX = startX + i * xOffset;
        itemY = InterfacePositions::LEVEL_SELECT_ITEM_Y_START +
                int(i / 10) * InterfacePositions::LEVEL_SELECT_ITEM_Y_OFFSET;
        
        levelBtn->setPosition(ccp(itemX,  itemY));
        if (i >= LevelProvider::getInstance()->getAvailableLevelsNum()) levelBtn->setEnabled(false);
        pMenu->addChild(levelBtn);
        _levelBtns->addObject(levelBtn);
    }
    
    
    pMenu->setPosition( cocos2d::CCPointZero );
    selBkgLevel->addChild(pMenu, 1);
 
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