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
#include "SwitchableObject.h"

class World;
class Ninja;

class Obstacle : public cocos2d::CCSprite, public SwitchableObject
{
public:
    static const char* WALL;
    static const char* WALKING_MINKER;
    static const char* DOOR;
    static const char* BUTTON;
    static const char* MACE;
    
    Obstacle(const int id) {
        _id = id;
    }
    
    inline const int getId() { return _id; }

    virtual bool checkHit(cocos2d::CCSprite* mapObject);
    virtual bool checkHeroDamage(Ninja* hero);
    virtual void interactWithWorld(World world);
    
    static Obstacle* createFromJSON(Json::Value obstacleJson);
    
    //switchable
    virtual void on(){}
    virtual void off(){}
    virtual bool isOn() { return true; }
    
protected:
    static const char* SAW_IMG;
    static const char* SAW_BKG_IMG;
    static const char* PUSH_BTN_ON_IMG;
    static const char* PUSH_BTN_OFF_IMG;
    static const char* WALL_IMG;
    static const char* FINISH_LIGHT_IMG;
    static const char* FINISH_IMG;
    static const char* MAULBALL_IMG;
    
private:
    int _id;
    
    static Obstacle* createWallMinker(Json::Value minkerJson);
    static Obstacle* createDoor(Json::Value doorJson);
    static Obstacle* createButton(Json::Value buttonJson);
    static Obstacle* createMace(Json::Value miceJson);
    static Obstacle* createWall(Json::Value wallJson);
    
    static cocos2d::CCPoint getItemPosition(Json::Value itemJson);
    static int getItemId(Json::Value itemJson);
};

#endif /* defined(__ninjaBall__Obstacle__) */
