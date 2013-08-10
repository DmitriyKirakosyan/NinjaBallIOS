#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Settings.h"
#include "SelectLevelScene.h"

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

    // create menu, it's an autorelease object

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Ninja Ball", "Thonburi", 34);

    // ask director the window size
    //CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT - 20) );


    CCSprite* background = CCSprite::create("MainMenuBG.png");
    background->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    this->addChild(background);
    
    CCMenuItemImage* pPlayBtn = CCMenuItemImage::create("Play@2x.png", "Play@2x.png",
                                                        this, menu_selector(MainScene::playCallback));
    CCMenuItemImage* pOptionsBtn = CCMenuItemImage::create("Options@2x.png", "Options@2x.png",
                                                           this, menu_selector(MainScene::optionsCallback));
    CCMenuItemImage* pCreditsBtn = CCMenuItemImage::create("Credits@2x.png", "Credits@2x.png",
                                                           this, menu_selector(MainScene::creditsCallback));
    
    float buttonsHeight = pPlayBtn->getContentSize().height +
                            pOptionsBtn->getContentSize().height +
                            pCreditsBtn->getContentSize().height;
    
    CCSize screenSize = CCSize(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT);
    pPlayBtn->setPosition( ccp(screenSize.width/2, screenSize.height/2 + buttonsHeight/2));
    pOptionsBtn->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    pCreditsBtn->setPosition(ccp(screenSize.width/2, screenSize.height/2 - buttonsHeight/2));

    pPlayBtn->setScale(0.6);
    pOptionsBtn->setScale(0.6);
    pCreditsBtn->setScale(0.6);

//    this->runAction(CCSequence::create(CCCallFuncO::create(this,  selector:@selector(tweenNode:) object:playButton],
//                     [CCCallFuncO actionWithTarget:self selector:@selector(tweenNode:) object:optionsButton],
//                     [CCCallFuncO actionWithTarget:self selector:@selector(tweenNode:) object:creditsButton],
//                     nil]];
    
    CCMenu* pMenu = CCMenu::create(pCloseItem, pPlayBtn, pOptionsBtn, pCreditsBtn, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    this->addChild(pLabel, 1);
    
    this->tweenNode(pPlayBtn);
    this->tweenNode(pOptionsBtn);
    this->tweenNode(pCreditsBtn);

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
