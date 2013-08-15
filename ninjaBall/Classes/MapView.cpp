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
#include "FinishLine.h"

using namespace cocos2d;

MapView::MapView(Ninja* ninja)
{
    _ninja = ninja;
    _finishLine = NULL;
    _obstacles = new ObstaclesController(this);
}

void MapView::tick()
{
    _obstacles->interact(_ninja);
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
    _finishLine = FinishLine::create();
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
    CCRect ninjaRect = ninja->getTextureRect();
    ninjaRect.origin = ccp(ninja->getPosition().x - ninja->getContentSize().width/2,
                            ninja->getPosition().y - ninja->getContentSize().height/2);
    
    CCRect finishRect = _finishLine->getTextureRect();
    finishRect.origin = ccp(_finishLine->getPosition().x - _finishLine->getContentSize().width/2,
                              _finishLine->getPosition().y - _finishLine->getContentSize().height/2);
    return (ninjaRect.intersectsRect(finishRect));
}