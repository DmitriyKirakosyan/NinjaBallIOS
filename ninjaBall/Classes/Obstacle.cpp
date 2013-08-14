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
#include "World.h"

using namespace cocos2d;

const char* Obstacle::YELLOW_MONSTER_IMG = "yellowMonster.png";
const char* Obstacle::RABBIT_MONSTER_IMG = "rabbitMonster.png";

const char* Obstacle::WALKING_MINKER = "walking_wall";
const char* Obstacle::WALL = "wall";
const char* Obstacle::MACE = "mace";
const char* Obstacle::DOOR = "door";
const char* Obstacle::BUTTON = "button";


bool Obstacle::checkHeroDamage(Ninja *hero)
{
    return false;
}

void Obstacle::interactWithWorld(World world)
{
    return; //nothing for basic obstacle;
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
    
    std::string type = obstacleJson.get("type", "").asCString();

    if (std::strcmp(type.c_str(), WALKING_MINKER) == 0)
    {
        result = createWallMinker(obstacleJson);
    }
    else
    {
        result = createWall(obstacleJson);
    }
    
    result->autorelease();
    return result;
}

//private

Obstacle* Obstacle::createWall(Json::Value wallJson)
{
    Obstacle* result = new Obstacle(0);
    result->initWithFile(YELLOW_MONSTER_IMG);
    result->setPosition(getItemPosition(wallJson));
    return result;
}

Obstacle* Obstacle::createWallMinker(Json::Value minkerJson)
{
    MovingObstacle* result = new MovingObstacle(0);
    result->setPosition(getItemPosition(minkerJson));
    
    Json::Value walkPath = minkerJson.get("walk_path", "");
    for (int i = 0; i < walkPath.size(); ++i) {
        result->addMovePoint(ccp(walkPath[i].get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                       walkPath[i].get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
    }
    return result;
}

CCPoint Obstacle::getItemPosition(Json::Value itemJson)
{
    float itemX = itemJson.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float itemY = itemJson.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    return ccp(itemX, itemY);
}