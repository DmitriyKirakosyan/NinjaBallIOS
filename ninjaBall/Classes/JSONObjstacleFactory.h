//
//  JSONObjstacleFactory.h
//  ninjaBall
//
//  Created by Dmitriy on 1/27/14.
//
//

#ifndef __ninjaBall__JSONObjstacleFactory__
#define __ninjaBall__JSONObjstacleFactory__

#include "json.h"
#include "cocos2d.h"


class Obstacle;


class JSONObjstacleFactory
{
public:
    static Obstacle* create(Json::Value obstacleJson);
    
private:
    static Obstacle* createWallMinker(Json::Value minkerJson);
    static Obstacle* createDoor(Json::Value doorJson);
    static Obstacle* createButton(Json::Value buttonJson);
    static Obstacle* createMace(Json::Value miceJson);
    static Obstacle* createWall(Json::Value wallJson);
    static Obstacle* createMaul(Json::Value maulJson);
    static Obstacle* createTesla(Json::Value teslaJson);
    
    static cocos2d::CCPoint getItemPosition(Json::Value itemJson);
    static int getItemId(Json::Value itemJson);

};

#endif /* defined(__ninjaBall__JSONObjstacleFactory__) */
