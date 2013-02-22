//
//  GameScene.h
//  ninjaBall
//
//  Created by Dmitriy on 2/13/13.
//
//

#ifndef __ninjaBall__GameScene__
#define __ninjaBall__GameScene__

#include "cocos2d.h"

class DrawingController;
class Ninja;
class ObstaclesController;

class GameScene : public cocos2d::CCScene
{
public:
    
    bool init();
    
    CREATE_FUNC(GameScene);
private:
    
};


class GameSceneLayer : public cocos2d::CCLayerColor
{
public:
    
    /**
     Стартует игру
     */
    void start();
    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    
private:
    Ninja* _ninja;
    
    cocos2d::CCArray* _touchPoints;
    
    DrawingController* _drawingController;
    
    ObstaclesController* _obstaclesController;
    
    bool _isDrawing;
    
    bool isPointUnderNinja(cocos2d::CCPoint point);
    
    void onNinjaMoveToPointComplete(cocos2d::CCNode* sender);
    
};

#endif /* defined(__ninjaBall__GameScene__) */
