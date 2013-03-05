//
//  LevelCompleteWindow.cpp
//  ninjaBall
//
//  Created by Dmitriy on 3/3/13.
//
//

#include "LevelCompleteWindow.h"
#include "LevelCompleteMenu.h"

using namespace cocos2d;

LevelCompleteWindow::LevelCompleteWindow(LevelCompleteMenu* levelCompleteMenu): _levelCompleteMenu(levelCompleteMenu)
{
    this->initWithFile("levelCompleteWindow.png");
    
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    
    cocos2d::CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                                            "CloseNormal.png",
                                                                            "CloseSelected.png",
                                                                            this, menu_selector(LevelCompleteWindow::menuCloseCallback) );
    pCloseItem->setPosition( ccp(winSize.width - 20, winSize.height / 2) );
    
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

