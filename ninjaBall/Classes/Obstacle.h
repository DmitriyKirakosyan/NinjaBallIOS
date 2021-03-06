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
    static const char* MAUL;
    static const char* TESLA;
    static const char* NOTYPE;
    
    Obstacle(const int id) {
        _id = id;
    }
    
    inline const int getId() { return _id; }
    
    virtual bool pathless() { return false; }

    virtual bool checkHit(cocos2d::CCSprite* mapObject);
    virtual bool checkHitWithPoint(cocos2d::CCPoint point);
    virtual bool checkHeroDamage(Ninja* hero) { return false; }
    virtual void interactWithWorld(World world);
    
    virtual const char* getType() { return NOTYPE; }
    
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
    static const char* MAULBASE_IMG;
    static const char* MAULROPE_IMG;
    
    
private:
    int _id;
    
};

#endif /* defined(__ninjaBall__Obstacle__) */
