//
//  ButtonObstacle.h
//  ninjaBall
//
//  Created by Dmitriy on 8/14/13.
//
//

#ifndef __ninjaBall__ButtonObstacle__
#define __ninjaBall__ButtonObstacle__

#include "Obstacle.h"

class SwitchableObject;
class IDoor;

class ButtonObstacle : public Obstacle
{
public:
    ButtonObstacle(const int id, const int switchableId):Obstacle(id)
    {
        _isOn = false;
        _switchableId = switchableId;
        _switchableObject = NULL;
        this->initWithFile(Obstacle::PUSH_BTN_OFF_IMG);
    }
    
    void addSwitchable(SwitchableObject* switchableObject)
    {
        _switchableObject = switchableObject;
    }
    
    //switchable
    void on();
    void off();
    inline bool isOn() { return _isOn; }
    
    void interactWithWorld(World world);
    
private:
    bool _isOn;
    int _switchableId;
    SwitchableObject* _switchableObject;
    
    SwitchableObject* getSwitchable(cocos2d::CCArray* obstacles);
};



#endif /* defined(__ninjaBall__ButtonObstacle__) */
