//
//  Obstacle.h
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#ifndef __ninjaBall__Obstacle__
#define __ninjaBall__Obstacle__

#include "cocos2d.h"
#include "json.h"

class Obstacle : public cocos2d::CCSprite
{
public:
    static const char* WALKING_WALL;
    
    Obstacle()
    {
    }
    
    Obstacle(const char* fileName, const cocos2d::CCPoint position);
    Obstacle(const char* behaviour);

    CREATE_FUNC(Obstacle);
    
    static Obstacle* createFromJSON(Json::Value obstacleJson);
    
private:
    
    static const char* getMonsterImage(const char* monsterType);
    
};

#endif /* defined(__ninjaBall__Obstacle__) */
