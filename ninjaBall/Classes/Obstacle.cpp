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
#include "ButtonObstacle.h"
#include "Door.h"
#include "World.h"

using namespace cocos2d;

const char* Obstacle::YELLOW_MONSTER_IMG = "yellowMonster.png";
const char* Obstacle::RABBIT_MONSTER_IMG = "rabbitMonster.png";
const char* Obstacle::BLUE_PORTAL_MONSTER_IMG = "bluePortalMonster.png";
const char* Obstacle::RED_RABBIT_MONSTER_IMG = "redRabbitMonster.png";


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
    const char* type_c = type.c_str();

    if (std::strcmp(type_c, WALKING_MINKER) == 0)
    {
        result = createWallMinker(obstacleJson);
    }
    else if (std::strcmp(type_c, WALL) == 0)
    {
        result = createWall(obstacleJson);
    }
    else if (std::strcmp(type_c, DOOR) == 0)
    {
        result = createDoor(obstacleJson);
    }
    else if (std::strcmp(type_c, BUTTON) == 0)
    {
        result = createButton(obstacleJson);
    }
    
    else
    {
        CCLOGERROR("unknown obstacle type");
        result = createWall(obstacleJson);
    }
    
    
    result->autorelease();
    return result;
}

//private

Obstacle* Obstacle::createWall(Json::Value wallJson)
{
    Obstacle* result = new Obstacle(getItemId(wallJson));
    result->initWithFile(YELLOW_MONSTER_IMG);
    result->setPosition(getItemPosition(wallJson));
    return result;
}

Obstacle* Obstacle::createWallMinker(Json::Value minkerJson)
{
    MovingObstacle* result = new MovingObstacle(getItemId(minkerJson));
    result->setPosition(getItemPosition(minkerJson));
    
    Json::Value walkPath = minkerJson.get("walk_path", "");
    for (int i = 0; i < walkPath.size(); ++i) {
        result->addMovePoint(ccp(walkPath[i].get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                       walkPath[i].get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
    }
    return result;
}

Obstacle* Obstacle::createButton(Json::Value buttonJson)
{
    int targetId = buttonJson.get("targetId", 0).asInt();
    ButtonObstacle* result = new ButtonObstacle(getItemId(buttonJson), targetId);
    result->initWithFile(RED_RABBIT_MONSTER_IMG);
    result->setPosition(getItemPosition(buttonJson));
    return result;
}

Obstacle* Obstacle::createDoor(Json::Value doorJson)
{
    Door* result = new Door(getItemId(doorJson));
    result->initWithFile(BLUE_PORTAL_MONSTER_IMG);
    result->setPosition(getItemPosition(doorJson));
    int state = doorJson.get("state", 0).asInt();
    if (state != 0) result->on();
    return result;
}

CCPoint Obstacle::getItemPosition(Json::Value itemJson)
{
    float itemX = itemJson.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float itemY = itemJson.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    return ccp(itemX, itemY);
}

int Obstacle::getItemId(Json::Value itemJson)
{
    return itemJson.get("id", 0).asInt();
}