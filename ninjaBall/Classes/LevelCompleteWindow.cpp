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
#include "InterfacePositions.h"

using namespace cocos2d;

LevelCompleteWindow::LevelCompleteWindow(LevelCompleteMenu* levelCompleteMenu): _levelCompleteMenu(levelCompleteMenu)
{
    this->initWithFile("LevelCompleteBkg.png");
    
    CCSprite* rollCircle = CCSprite::create("ShineStar.png");
    rollCircle->setPosition(ccp(InterfacePositions::LEVEL_COMPLETE_CIRCLE_X,
                                InterfacePositions::LEVEL_COMPLETE_CIRCLE_Y));
    rollCircle->runAction(CCRepeatForever::create(CCRotateBy::create(1, 10)));

    
    this->addChild(rollCircle);

    
    //CCSprite* cup = CCSprite::create(")
    
    
    
    cocos2d::CCMenuItemImage *pCloseItem =
                    CCMenuItemImage::create("BackToMainBtn_1.png",
                                            "BackToMainBtn_2.png",
                                            this, menu_selector(LevelCompleteWindow::menuCloseCallback) );
    cocos2d::CCMenuItemImage *pReplayItem =
                    CCMenuItemImage::create("ReplayLvlBtn_1.png",
                                            "ReplayLvlBtn_2.png",
                                            this, menu_selector(LevelCompleteWindow::menuReplayCallback) );
    cocos2d::CCMenuItemImage *pNextItem =
                    CCMenuItemImage::create("NextLvlBtn_1.png",
                                            "NextLvlBtn_2.png",
                                            this, menu_selector(LevelCompleteWindow::menuNextCallback) );
    
    CCSize windowSize = this->getContentSize();
    pCloseItem->setPosition( ccp(InterfacePositions::LEVEL_COMPLETE_TOMENU_X +
                                 pCloseItem->getContentSize().width/2,
                                 InterfacePositions::LEVEL_COMPLETE_TOMENU_Y -
                                 pCloseItem->getContentSize().height/2));
    pReplayItem->setPosition(ccp(InterfacePositions::LEVEL_COMPLETE_REPLAY_X +
                                 pReplayItem->getContentSize().width/2,
                                 InterfacePositions::LEVEL_COMPLETE_REPLAY_Y -
                                 pReplayItem->getContentSize().height/2));
    pNextItem->setPosition(ccp(InterfacePositions::LEVEL_COMPLETE_NEXTLVL_X +
                               pNextItem->getContentSize().width/2,
                               InterfacePositions::LEVEL_COMPLETE_NEXTLVL_Y -
                               pNextItem->getContentSize().height/2));
    
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

