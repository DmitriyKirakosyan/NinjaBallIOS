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

class ObstaclesController
{
public:
    ObstaclesController(cocos2d::CCLayer* mapLayer, cocos2d::CCSize winSize);
    
    void createRandomObstacles();
    void clear();
  
private:
    cocos2d::CCSize _winsize;
    cocos2d::CCArray* _obstacles;
    cocos2d::CCLayer* _mapLayer;
    
    const unsigned int MONSTERS_NUM;
};

#endif /* defined(__ninjaBall__ObstaclesController__) */
