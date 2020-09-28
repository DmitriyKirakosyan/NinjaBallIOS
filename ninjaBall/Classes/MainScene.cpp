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

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLog("visible size : %f, %f", visibleSize.width, visibleSize.height);
    CCLog("visible origin : %f, %f", origin.x, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(MainScene::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    
    CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();


//    std::string fullFilePath = fileUtils->fullPathFromRelativePath("mainMenu/mainMenuBkg.png");
    std::string fullFilePath = fileUtils->fullPathForFilename("mainMenu/mainMenuBkg.png");
    CCLog("file path : %s", fullFilePath.c_str());
    CCSprite* background = CCSprite::create("mainMenu/mainMenuBkg.png");
    background->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    this->addChild(background);
    

    
    CCMenuItemImage* pPlayBtn = CCMenuItemImage::create("mainMenu/startBtn_1.png", "mainMenu/startBtn_2.png",
                                                        this, menu_selector(MainScene::playCallback));
    CCMenuItemImage* pOptionsBtn = CCMenuItemImage::create("mainMenu/optionsBtn_1.png", "mainMenu/optionsBtn_2.png",
                                                           this, menu_selector(MainScene::optionsCallback));
    CCMenuItemImage* pCreditsBtn = CCMenuItemImage::create("mainMenu/aboutBtn_1.png", "mainMenu/aboutBtn_2.png",
                                                           this, menu_selector(MainScene::creditsCallback));
    
    pPlayBtn->setPosition( ccp(InterfacePositions::MENU_PLAY_BTN_X, InterfacePositions::MENU_PLAY_BTN_Y));
    pOptionsBtn->setPosition(ccp(InterfacePositions::MENU_OPTIONS_BTN_X, InterfacePositions::MENU_OPTIONS_BTN_Y));
    pCreditsBtn->setPosition(ccp(InterfacePositions::MENU_ABOUT_BTN_X, InterfacePositions::MENU_ABOUT_BTN_Y));


    CCMenu* pMenu = CCMenu::create(pPlayBtn, pOptionsBtn, pCreditsBtn, NULL);
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
