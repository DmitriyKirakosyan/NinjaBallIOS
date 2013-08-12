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

const char* Obstacle::YELLOW_MONSTER_IMG = "yellowMonster.png";
const char* Obstacle::RABBIT_MONSTER_IMG = "rabbitMonster.png";

const char* Obstacle::WALKING_WALL = "walking_wall";


bool Obstacle::checkHeroDamage(Ninja *hero)
{
    return false;
}

bool Obstacle::checkHit(cocos2d::CCSprite *mapObject)
{
    CCRect objectRect = mapObject->getTextureRect();
    objectRect.origin = ccp(mapObject->getPosition().x - mapObject->getContentSize().width/2,
                            mapObject->getPosition().y - mapObject->getContentSize().height/2);
    
    CCRect obstacleRect = this->getTextureRect();
    obstacleRect.origin = ccp(this->getPosition().x - this->getContentSize().width/2,
                              this->getPosition().y - this->getContentSize().height/2);
    if (objectRect.intersectsRect(obstacleRect))
    {
        return true;
    }
    return false;
}

Obstacle* Obstacle::createFromJSON(Json::Value obstacleJson)
{
    Obstacle* result;
    float itemX = obstacleJson.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float itemY = obstacleJson.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    
    
    std::string type = obstacleJson.get("type", "").asCString();

    if (std::strcmp(type.c_str(), WALKING_WALL) == 0)
    {
        result = new MovingObstacle();
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
        result->initWithFile(YELLOW_MONSTER_IMG);
        result->setPosition(ccp(itemX, itemY));
    }
    
    result->autorelease();
    return result;
}