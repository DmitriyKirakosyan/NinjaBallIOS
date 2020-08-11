//
//  GameWindowFactory.h
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#ifndef __ninjaBall__GameWindowFactory__
#define __ninjaBall__GameWindowFactory__

#include "AWindowFactory.h"

class GameSceneLayer;
class LevelCompleteMenu;

class GameWindowFactory : public AWindowFactory
{
public:
    GameWindowFactory(GameSceneLayer* gameLayer): _gameLayer(gameLayer)
    {
        
    }
    
    AWindow* getWindow(const char* windowName);
    
    
    static const char* LEVEL_COMPLETE_WINDOW;
    
private:
    GameSceneLayer* _gameLayer;
};

#endif /* defined(__ninjaBall__GameWindowFactory__) */
