//
//  Obstacle.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#include "Obstacle.h"
#include "Settings.h"
#include "MovingObstacle.h"

using namespace cocos2d;

const char* Obstacle::WALKING_WALL = "walking_wall";

Obstacle::Obstacle(const char* behaviour)
{
    Obstacle();
}

Obstacle::Obstacle(const char* fileName, const CCPoint position)
{
    Obstacle();
    this->initWithFile(fileName);
    this->setPosition(position);
}

Obstacle* Obstacle::createFromJSON(Json::Value obstacleJson)
{
    Obstacle* result;
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float itemX = obstacleJson.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float itemY = obstacleJson.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    
    CCLog("type of monster char* : %s", obstacleJson.get("type", "").asCString());
    CCLog("type of monster std::string : %s", obstacleJson.get("type", "").asString().c_str());
    
    
    std::string type = obstacleJson.get("type", "").asCString();
    CCLog("var type : %s", type.c_str());

    const char* monsterImage = Obstacle::getMonsterImage(type.c_str());
    if (std::strcmp(type.c_str(), WALKING_WALL) == 0)
    {
        result = new MovingObstacle();
        result->initWithFile(monsterImage);
        result->setPosition(ccp(itemX, itemY));
        
        Json::Value walkPath = obstacleJson.get("walk_path", "");
        MovingObstacle* movingResult = (MovingObstacle*) result;
        for (int i = 0; i < walkPath.size(); ++i) {
            movingResult->addMovePoint(ccp(walkPath[i].get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                     walkPath[i].get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
        }
    }
    else
    {
        result = new Obstacle();
        result->initWithFile(monsterImage);
        result->setPosition(ccp(itemX, itemY));
    }
    
    result->autorelease();
    return result;
}

const char* Obstacle::getMonsterImage(const char* monsterType)
{
    CCLog("strings : %s, %s", monsterType, WALKING_WALL);
    const char* result;
    if (std::strcmp(monsterType, WALKING_WALL) == 0) {
        result = "yellowMonster.png";
    }
    else
    {
        CCLOGERROR("unknown monster type");
        result = "yellowMonster.png";
    }
    CCLog("strings : %s, %s", monsterType, WALKING_WALL);
    return result;
}