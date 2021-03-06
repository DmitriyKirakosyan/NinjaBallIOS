//
//  ObstaclesController.h
//  ninjaBall
//
//  Created by Dmitriy on 2/21/13.
//
//

#ifndef __ninjaBall__ObstaclesController__
#define __ninjaBall__ObstaclesController__

#include "cocos2d.h"
#include "json.h"
#include "World.h"


class Ninja;
class World;
class TeslaInteraction;

class ObstaclesController
{
public:
    ObstaclesController(cocos2d::CCLayer* mapLayer);
    
    void interact(Ninja* ninja);
    
    bool testHit(cocos2d::CCSprite* object);
    bool testHitWithPoint(cocos2d::CCPoint point);
    bool testDamage(Ninja* ninja);
    
    bool isPointPathless(cocos2d::CCPoint point);

    void createFromJSON(Json::Value jsonValue);
    
    void createFromTMX(cocos2d::CCTMXTiledMap* tileMap);
    
    void clear();
  
private:
    cocos2d::CCArray* _obstacles;
    cocos2d::CCLayer* _mapLayer;
    
    TeslaInteraction* _teslaInteraction;
    
    World _world;
    
    const unsigned int MONSTERS_NUM;
};

#endif /* defined(__ninjaBall__ObstaclesController__) */
