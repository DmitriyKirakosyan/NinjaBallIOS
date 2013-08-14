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
#include "LevelCompleteMenu.h"

class DrawingController;
class Ninja;
class MapView;
class WindowManager;

class GameScene : public cocos2d::CCScene
{
public:
    
    
    static GameScene* create(const char* levelName);
    
    
private:
    bool init(const char* levelName);
    
};


class GameSceneLayer : public cocos2d::CCLayerColor, public LevelCompleteMenu
{
public:
    
    /**
     Стартует игру
     */
    void start(const char* levelName);
    
    /**
     Стартует уровень
     */
    void startLevel(const char * levelName);
    
    virtual void update(float dt);
    
    //level complete menu interface
    virtual void nextLevel();
    virtual void replyLevel();
    virtual void returnToMainMenu();
    virtual bool canStartNextLevel();
    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    cocos2d::CCLayer* getWindowLayer();

    
private:
    std::string _currentLevelName;
    
    Ninja* _ninja;
    
    cocos2d::CCArray* _touchPoints;
    
    WindowManager* _windowManager;
    
    DrawingController* _drawingController;
    
    MapView* _mapView;
    
    bool _isDrawing;
    
    bool isPointUnderNinja(cocos2d::CCPoint point);
    
    void onNinjaMoveToPointComplete(cocos2d::CCNode* sender);
    
};

#endif /* defined(__ninjaBall__GameScene__) */
