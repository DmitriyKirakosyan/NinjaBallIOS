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
    ButtonObstacle(const char* id, const char* switchableId):Obstacle(id)
    {
        _switchableId = switchableId;
    }
    
    void addSwitchable(SwitchableObject* switchableObject)
    {
        _switchableObject = switchableObject;
    }
    
    void interactWithWorld(World world);
    
private:
    const char* _switchableId;
    SwitchableObject* _switchableObject;
    
    SwitchableObject* getSwitchable(cocos2d::CCArray* obstacles);
};



#endif /* defined(__ninjaBall__ButtonObstacle__) */
