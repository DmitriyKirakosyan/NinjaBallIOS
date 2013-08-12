//
//  MapView.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#include "MapView.h"
#include "ObstaclesController.h"
#include "json.h"
#include <fstream>
#include "Ninja.h"
#include "Settings.h"

using namespace cocos2d;

MapView::MapView(Ninja* ninja)
{
    _ninja = ninja;
    _finishLine = NULL;
    _obstacles = new ObstaclesController(this);
}

void MapView::createLevel(const char *fileName)
{
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
    const char *pszPath = fileUtils->fullPathFromRelativePath(fileName);
    std::ifstream jsonFile(pszPath);
    
    bool parsingSuccessful = reader.parse(jsonFile, root);
    CCAssert(parsingSuccessful, "parse problem" + reader.getFormatedErrorMessages());

    Json::Value ninjaValue = root.get("ninja", "");
    float ninjaX = ninjaValue.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float ninjaY = ninjaValue.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    _ninja->setPosition(ccp(ninjaX, ninjaY));
    
    Json::Value flValue = root.get("finish_line", "");
    _finishLine = CCSprite::create("flags.png");
    _finishLine->setScale(0.5f);
    _finishLine->setPosition(ccp(flValue.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                 flValue.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
    this->addChild(_finishLine);
    
    _obstacles->createFromJSON(root.get("map_objects", ""));

}

void MapView::clear()
{
    _obstacles->clear();
    if (_finishLine != NULL)
    {
        this->removeChild(_finishLine, false);
        _finishLine = NULL;
    }
}

bool MapView::isNinjaWin(CCSprite* ninja)
{
    CCRect ninjaRect = CCRectMake(
                                   ninja->getPosition().x - ninja->getContentSize().width/4,
                                   ninja->getPosition().y - ninja->getContentSize().height/4,
                                   ninja->getContentSize().width/2,
                                   ninja->getContentSize().height/2);
    CCRect finishLineRect = CCRectMake(
                                       _finishLine->getPosition().x - _finishLine->getContentSize().width/8,
                                       _finishLine->getPosition().y - _finishLine->getContentSize().height/8,
                                       _finishLine->getContentSize().width/4, _finishLine->getContentSize().height/4);
    return ninjaRect.intersectsRect(finishLineRect);
}