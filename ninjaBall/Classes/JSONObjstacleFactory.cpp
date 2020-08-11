//
//  JSONObjstacleFactory.cpp
//  ninjaBall
//
//  Created by Dmitriy on 1/27/14.
//
//

#include "JSONObjstacleFactory.h"
#include "Obstacle.h"
#include "Wall.h"
#include "MovingSaw.h"
#include "ButtonObstacle.h"
#include "Door.h"
#include "Maul.h"
#include "TeslaItem.h"
#include "Settings.h"

using namespace cocos2d;

Obstacle* JSONObjstacleFactory::create(Json::Value obstacleJson)
{
    Obstacle* result;
    
    std::string type = obstacleJson.get("type", "").asCString();
    const char* type_c = type.c_str();
    
    if (std::strcmp(type_c, Obstacle::WALKING_MINKER) == 0)
    {
        result = createWallMinker(obstacleJson);
    }
    else if (std::strcmp(type_c, Obstacle::WALL) == 0)
    {
        result = createWall(obstacleJson);
    }
    else if (std::strcmp(type_c, Obstacle::DOOR) == 0)
    {
        result = createDoor(obstacleJson);
    }
    else if (std::strcmp(type_c, Obstacle::BUTTON) == 0)
    {
        result = createButton(obstacleJson);
    }
    else if (std::strcmp(type_c, Obstacle::MAUL) == 0)
    {
        result = createMaul(obstacleJson);
    }
    else if (std::strcmp(type_c, Obstacle::TESLA) == 0)
    {
        result = createTesla(obstacleJson);
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

Obstacle* JSONObjstacleFactory::createWall(Json::Value wallJson)
{
    Obstacle* result = new Wall(getItemId(wallJson));
    result->setPosition(getItemPosition(wallJson));
    return result;
}

Obstacle* JSONObjstacleFactory::createWallMinker(Json::Value minkerJson)
{
    MovingSaw* result = new MovingSaw(getItemId(minkerJson));
    result->setPosition(getItemPosition(minkerJson));
    
    Json::Value walkPath = minkerJson.get("walk_path", "");
    for (int i = 0; i < walkPath.size(); ++i) {
        result->addMovePoint(ccp(walkPath[i].get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                 walkPath[i].get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
    }
    return result;
}

Obstacle* JSONObjstacleFactory::createButton(Json::Value buttonJson)
{
    int targetId = buttonJson.get("targetId", 0).asInt();
    ButtonObstacle* result = new ButtonObstacle(getItemId(buttonJson), targetId);
    result->setPosition(getItemPosition(buttonJson));
    return result;
}

Obstacle* JSONObjstacleFactory::createDoor(Json::Value doorJson)
{
    Obstacle* result = new Door(getItemId(doorJson));
    result->setPosition(getItemPosition(doorJson));
    int state = doorJson.get("state", 0).asInt();
    if (state != 0) result->on();
    return result;
}

Obstacle* JSONObjstacleFactory::createMaul(Json::Value maulJson)
{
    float rotationSpeed = 1.0f / (float)maulJson.get("rotationSpeed", 1).asDouble();
    Maul* result = new Maul(getItemId(maulJson), rotationSpeed);
    result->setPosition(getItemPosition(maulJson));
    return result;
}

Obstacle* JSONObjstacleFactory::createTesla(Json::Value teslaJson)
{
    int friendId = teslaJson.get("friend", 0).asInt();
    TeslaItem* result = new TeslaItem(getItemId(teslaJson), friendId);
    result->setPosition(getItemPosition(teslaJson));
    Json::Value walkPath = teslaJson.get("walk_path", "");
    for (int i = 0; i < walkPath.size(); ++i) {
        result->addMovePoint(ccp(walkPath[i].get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH,
                                 walkPath[i].get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT));
    }
    return result;
}


CCPoint JSONObjstacleFactory::getItemPosition(Json::Value itemJson)
{
    float itemX = itemJson.get("x", 0).asDouble() * Settings::VIRTUAL_WIDTH;
    float itemY = itemJson.get("y", 0).asDouble() * Settings::VIRTUAL_HEIGHT;
    return ccp(itemX, itemY);
}

int JSONObjstacleFactory::getItemId(Json::Value itemJson)
{
    return itemJson.get("id", 0).asInt();
}

