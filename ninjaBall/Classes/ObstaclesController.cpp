//
//  ObstaclesController.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#include "ObstaclesController.h"

using namespace cocos2d;

ObstaclesController::ObstaclesController(CCLayer* mapLayer, CCSize winSize):MONSTERS_NUM(12)
{
    _obstacles = NULL;
    _mapLayer = mapLayer;
    _winsize = winSize;
}

void ObstaclesController::clear()
{
    if (_obstacles)
    {
        CCObject* obstacleItem;
        CCARRAY_FOREACH(_obstacles, obstacleItem)
        {
            if (_mapLayer->getChildren()->containsObject(obstacleItem))
            {
                _mapLayer->removeChild((CCSprite*) obstacleItem, true);
            }
        }
        _obstacles->removeAllObjects();
        _obstacles = NULL;
    }
}

void ObstaclesController::createRandomObstacles()
{
    int obstaclesNum = arc4random() % 3 + 2;
    char* sImageNumber;
    char* imagePath;
    int imageNumber;
    float imageX, imageY;
    CCSprite* obstacle;
    for (int i = 0; i < obstaclesNum; ++i) {
        imageNumber = arc4random() % MONSTERS_NUM;
        sImageNumber = new char[((sizeof (imageNumber + 1) * CHAR_BIT) + 2)/3 + 2];
        sprintf(sImageNumber, "%d", imageNumber + 1);
        imagePath = strcat(sImageNumber, ".png");
        
        obstacle = CCSprite::create(imagePath);
        obstacle->setScale(0.5f);
        
        imageX = (arc4random() % (int)(_winsize.width - obstacle->getContentSize().width)) +
                                        obstacle->getContentSize().width/2;
        imageY = (arc4random() % (int)(_winsize.height - obstacle->getContentSize().height)) +
                                        obstacle->getContentSize().height/2;
        obstacle->setPosition(ccp(imageX, imageY));
        _mapLayer->addChild(obstacle);
    }
}