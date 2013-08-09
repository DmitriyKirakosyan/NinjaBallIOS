//
//  LevelCompleteWindow.cpp
//  ninjaBall
//
//  Created by Dmitriy on 3/3/13.
//
//

#include "LevelCompleteWindow.h"
#include "LevelCompleteMenu.h"
#include "Settings.h"

using namespace cocos2d;

LevelCompleteWindow::LevelCompleteWindow(LevelCompleteMenu* levelCompleteMenu): _levelCompleteMenu(levelCompleteMenu)
{
    this->initWithFile("levelCompleteWindow.png");
    
    //cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    
    //CCLog("width : %f, height : %f", winSize.width, winSize.height);
    
    CCLog("width : %i", Settings::VIRTUAL_WIDTH);
    
    cocos2d::CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                                            "CloseNormal.png",
                                                                            "CloseSelected.png",
                                                                            this, menu_selector(LevelCompleteWindow::menuCloseCallback) );
    
    CCSize windowSize = this->getContentSize();
    pCloseItem->setPosition( ccp(windowSize.width - pCloseItem->getContentSize().width/2,
                                 windowSize.height - pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( cocos2d::CCPointZero );
    this->addChild(pMenu, 1);
}

void LevelCompleteWindow::menuCloseCallback(cocos2d::CCObject* pSender)
{
    this->setReadyToClose(true);
    _levelCompleteMenu->nextLevel();
}

