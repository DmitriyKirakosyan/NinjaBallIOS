#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Settings.h"
#include "SelectLevelScene.h"
#include "InterfacePositions.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    scene->setAnchorPoint(CCPointZero);
    scene->setScale(Settings::density);
    scene->setPosition(ccp(Settings::REAL_WIDTH_OFFSET, Settings::REAL_HEIGHT_OFFSET));
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    
    CCSprite* background = CCSprite::create("mainMenuBkg.png");
    background->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    this->addChild(background);
    
    CCMenuItemImage* pPlayBtn = CCMenuItemImage::create("startBtn_1.png", "startBtn_2.png",
                                                        this, menu_selector(MainScene::playCallback));
    CCMenuItemImage* pOptionsBtn = CCMenuItemImage::create("optionsBtn_1.png", "optionsBtn_2.png",
                                                           this, menu_selector(MainScene::optionsCallback));
    CCMenuItemImage* pCreditsBtn = CCMenuItemImage::create("aboutBtn_1.png", "aboutBtn_2.png",
                                                           this, menu_selector(MainScene::creditsCallback));
    
    pPlayBtn->setPosition( ccp(InterfacePositions::MENU_PLAY_BTN_X, InterfacePositions::MENU_PLAY_BTN_Y));
    pOptionsBtn->setPosition(ccp(InterfacePositions::MENU_OPTIONS_BTN_X, InterfacePositions::MENU_OPTIONS_BTN_Y));
    pCreditsBtn->setPosition(ccp(InterfacePositions::MENU_ABOUT_BTN_X, InterfacePositions::MENU_ABOUT_BTN_Y));


    CCMenu* pMenu = CCMenu::create(pCloseItem, pPlayBtn, pOptionsBtn, pCreditsBtn, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    return true;
}

void MainScene::tweenNode(CCNode  * menuItem) {
    menuItem->runAction(CCEaseElasticOut::create(CCScaleTo::create(1.7, 1)));
}


void MainScene::playCallback(CCObject* pSender)
{
    CCScene* scene = SelectLevelScene::scene();
    //GameScene* gameScene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void MainScene::optionsCallback(cocos2d::CCObject *pSender)
{
    
}

void MainScene::creditsCallback(cocos2d::CCObject *pSender)
{
    
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
