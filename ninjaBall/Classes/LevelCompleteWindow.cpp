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
#include "AWindowParams.h"
#include "LevelCompleteWindowParams.h"

using namespace cocos2d;

LevelCompleteWindow::LevelCompleteWindow(LevelCompleteMenu* levelCompleteMenu): _levelCompleteMenu(levelCompleteMenu)
{
    _stars = NULL;
    this->initWithFile("levelCompleteWindow/LevelCompleteBkg.png");
    
    CCSprite* rollCircle = CCSprite::create("levelCompleteWindow/shineStar.png");
    rollCircle->setPosition(ccp(InterfacePositions::LEVEL_COMPLETE_CIRCLE_X,
                                InterfacePositions::LEVEL_COMPLETE_CIRCLE_Y));
    rollCircle->runAction(CCRepeatForever::create(CCRotateBy::create(1, 10)));

    
    this->addChild(rollCircle);

    
    //CCSprite* cup = CCSprite::create(")
    
    
    
    cocos2d::CCMenuItemImage *pCloseItem =
                    CCMenuItemImage::create("levelCompleteWindow/BackToMainBtn_1.png",
                                            "levelCompleteWindow/BackToMainBtn_2.png",
                                            this, menu_selector(LevelCompleteWindow::menuCloseCallback) );
    cocos2d::CCMenuItemImage *pReplayItem =
                    CCMenuItemImage::create("levelCompleteWindow/ReplayLvlBtn_1.png",
                                            "levelCompleteWindow/ReplayLvlBtn_2.png",
                                            this, menu_selector(LevelCompleteWindow::menuReplayCallback) );
    cocos2d::CCMenuItemImage *pNextItem =
                    CCMenuItemImage::create("levelCompleteWindow/nextLvlBtn_1.png",
                                            "levelCompleteWindow/NextLvlBtn_2.png",
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

void LevelCompleteWindow::open(AWindowParams& params)
{
    CCAssert(params.getType() == AWindowParams::LEVEL_COMPLETE_PARAMS, "wrong params for level complete level window");
    LevelCompleteWindowParams levCmpParams = (LevelCompleteWindowParams&) params;

    _stars = new CCArray();
    float lineWidth = this->getContentSize().width - 200;
    float cellWidth = lineWidth / STARS_NUM;
    int goldNum = arc4random() % 4;
    CCLog("gold num : %d", goldNum);
    for (int i = 0; i < STARS_NUM; ++i)
    {
        
        CCSprite* star;
        if (i < goldNum)
        {
            star = CCSprite::create("levelCompleteWindow/star_2.png");
            star->setScale(0.9);
            star->runAction(CCEaseElasticOut::create(CCScaleTo::create(1.7, 1)));
        }
        else
        {
            star = CCSprite::create("levelCompleteWindow/star_1.png");
        }

        star->setPosition(ccp(100 + i * cellWidth, 267));
        this->addChild(star);
    }
}

void LevelCompleteWindow::close()
{
    AWindow::close();
    if (_stars != NULL) {
        CCObject* star;
        CCARRAY_FOREACH(_stars, star)
        {
            this->removeChild((CCSprite*)star, true);
        }
        _stars->removeAllObjects();
        delete _stars;
        _stars = NULL;
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

