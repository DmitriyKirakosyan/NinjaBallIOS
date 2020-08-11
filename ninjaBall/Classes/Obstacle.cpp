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
#include "Maul.h"
#include "TeslaItem.h"
#include "MovingSaw.h"
#include "Wall.h"

using namespace cocos2d;

const char* Obstacle::WALL_IMG = "mapObjects/box.png";
const char* Obstacle::SAW_BKG_IMG = "mapObjects/sawBkg.png";
const char* Obstacle::SAW_IMG = "mapObjects/saw.png";
const char* Obstacle::PUSH_BTN_ON_IMG = "mapObjects/pushBtn_2.png";
const char* Obstacle::PUSH_BTN_OFF_IMG = "mapObjects/pushBtn_1.png";
const char* Obstacle::FINISH_IMG = "mapObjects/finish.png";
const char* Obstacle::FINISH_LIGHT_IMG = "mapObjects/finishLight.png";
const char* Obstacle::MAULBALL_IMG = "mapObjects/maulBall.png";
const char* Obstacle::MAULBASE_IMG = "mapObjects/maulBase.png";
const char* Obstacle::MAULROPE_IMG = "mapObjects/maulRope.png";



const char* Obstacle::WALKING_MINKER = "walking_wall";
const char* Obstacle::WALL = "wall";
const char* Obstacle::MACE = "mace";
const char* Obstacle::DOOR = "door";
const char* Obstacle::BUTTON = "button";
const char* Obstacle::MAUL = "maul";
const char* Obstacle::TESLA = "tesla";
const char* Obstacle::NOTYPE = "no_type";


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
    
    
    CCParticleSystem* skin = new CCParticleSystem();
    CCSize mySize = CCSize(3, 4);
    skin->setContentSize(mySize);
    //CCSize mySize = CCSize()(3, 4);
    
    return objectRect.intersectsRect(obstacleRect);
}

bool Obstacle::checkHitWithPoint(cocos2d::CCPoint point)
{
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    cocos2d::CCRect obstacleRect = cocos2d::CCRect(this->getPosition().x - width/2,
                                                   this->getPosition().y - height/2,
                                                   width, height);
    
    return obstacleRect.containsPoint(point);
}

