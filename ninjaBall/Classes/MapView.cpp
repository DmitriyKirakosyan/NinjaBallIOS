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
    unsigned long* pSize = new unsigned long[10];

    std::string strPath = fileUtils->fullPathForFilename(fileName);
    const char* path = strPath.c_str();
    std::string fileData = std::string(reinterpret_cast<const char*>(fileUtils->getFileData(path, "r", pSize)));
    //std::ifstream jsonFile(pszPath.c_str());

    //CCLog("file full path : %s", pszPath.c_str());

    
    bool parsingSuccessful = reader.parse(fileData, root);//jsonFile, root);
    //TODO need to copy string with format
    CCAssert(parsingSuccessful, "parse problem");// + reader.getFormatedErrorMessages());

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

void MapView::createLevelFromTMX(const char *fileName)
{
    CCTMXTiledMap* tileMap = CCTMXTiledMap::create(fileName);
    _obstacles->createFromTMX(tileMap);
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

CCPoint MapView::restrictPath(CCPoint startPoint, CCPoint endPoint)
{
    int stepsNum = (int) distanceBetween(startPoint, endPoint) / 5.0f;
    CCPoint pointOnLine;
    int i;
    for (i = 0; i < stepsNum; ++i) {
        pointOnLine = ccpLerp(startPoint, endPoint, (i+1) / (float)stepsNum);
        if (_obstacles->isPointPathless(pointOnLine))
        {
            break;
        }
    }
    
    CCPoint result;
    if (i < stepsNum)
    {
        if (i > 2)
        {
            result = ccpLerp(startPoint, endPoint, (i-2) / stepsNum);
        }
        else result = startPoint;
    }
    else result = endPoint;
    
    return result;
}

float MapView::distanceBetween(CCPoint p1, CCPoint p2)
{
    return sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
}
