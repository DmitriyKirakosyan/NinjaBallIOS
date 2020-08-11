//
//  MapObject.h
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#ifndef ninjaBall_MapObject_h
#define ninjaBall_MapObject_h

#include "cocos2d.h";

class MapObject : public cocos2d::CCSprite
{
public:
    void rotateTo(float x, float y)
    {
        float dx = this->getPosition().x - x;
        float dy = this->getPosition().y - y;
        float angle = 90 + atan2f(dy, dx) * 180 / 3.14;
        this->setRotation(-angle);
    }
};

#endif
