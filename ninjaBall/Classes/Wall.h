//
//  Wall.h
//  ninjaBall
//
//  Created by Dmitriy on 8/20/13.
//
//

#ifndef ninjaBall_Wall_h
#define ninjaBall_Wall_h

#include "Obstacle.h"

class Wall : public Obstacle
{
public:
    Wall(const int itemId):Obstacle(itemId)
    {
        this->initWithFile(WALL_IMG);
    }
    
    const char* getType() { return Obstacle::WALL; }
    
    bool pathless() { return true; }
    
    bool checkHitWithPoint(cocos2d::CCPoint point)
    {
        float width = this->getContentSize().width * 2;
        float height = this->getContentSize().height * 2;
        cocos2d::CCRect obstacleRect = cocos2d::CCRect(this->getPosition().x - width/2,
                                     this->getPosition().y - height/2,
                                     width, height);
        
        return obstacleRect.containsPoint(point);
    }
    
};


#endif
