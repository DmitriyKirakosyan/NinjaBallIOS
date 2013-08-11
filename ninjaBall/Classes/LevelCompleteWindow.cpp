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
    
    cocos2d::CCMenuItemImage *pCloseItem =
                    CCMenuItemImage::create("Left.png",
                                            "Left.png",
                                            this, menu_selector(LevelCompleteWindow::menuCloseCallback) );
    cocos2d::CCMenuItemImage *pReplayItem =
                    CCMenuItemImage::create("Replay.png",
                                            "Replay.png",
                                            this, menu_selector(LevelCompleteWindow::menuReplayCallback) );
    cocos2d::CCMenuItemImage *pNextItem =
                    CCMenuItemImage::create("Right-Play.png",
                                            "Right-Play.png",
                                            this, menu_selector(LevelCompleteWindow::menuNextCallback) );
    
    float buttonsWidth = pCloseItem->getContentSize().width +
                         pReplayItem->getContentSize().width +
                         pNextItem->getContentSize().width;
    
    CCSize windowSize = this->getContentSize();
    pCloseItem->setPosition( ccp(windowSize.width/2 - buttonsWidth/2, windowSize.height/2));
    pReplayItem->setPosition(ccp(windowSize.width/2, windowSize.height/2));
    pNextItem->setPosition(ccp(windowSize.width/2 + buttonsWidth/2, windowSize.height/2));
    
    // create menu, it's an autorelease object
    cocos2d::CCMenu* pMenu = cocos2d::CCMenu::create(pCloseItem, pReplayItem, pNextItem, NULL);
    pMenu->setPosition( cocos2d::CCPointZero );
    this->addChild(pMenu, 1);
    
    if (!levelCompleteMenu->canStartNextLevel()) {
        pNextItem->setEnabled(false);
    }
}

void LevelCompleteWindow::menuCloseCallback(cocos2d::CCObject *pSender)
{
    this->setReadyToClose(true);
    _levelCompleteMenu->returnToMainMenu();
}

void LevelCompleteWindow::menuReplayCallback(cocos2d::CCObject *pSender)
{
    this->setReadyToClose(true);
    _levelCompleteMenu->replyLevel();
}

void LevelCompleteWindow::menuNextCallback(cocos2d::CCObject* pSender)
{
    this->setReadyToClose(true);
    _levelCompleteMenu->nextLevel();
}

