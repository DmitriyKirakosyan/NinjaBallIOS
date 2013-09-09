//
//  LevelCompleteWindow.h
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#ifndef ninjaBall_LevelCompleteWindow_h
#define ninjaBall_LevelCompleteWindow_h

#include "AWindow.h"

class LevelCompleteMenu;

//using namespace cocos2d;

class LevelCompleteWindow : public AWindow
{
public:
    LevelCompleteWindow(LevelCompleteMenu* levelCompleteMenu);
    
    void menuCloseCallback(cocos2d::CCObject* pSender);
    void menuNextCallback(cocos2d::CCObject* pSender);
    void menuReplayCallback(cocos2d::CCObject* pSender);
    
    void open(AWindowParams& params);
    void close();
    
private:
    
    static const int STARS_NUM = 3;
    
    LevelCompleteMenu* _levelCompleteMenu;
    
    cocos2d::CCArray* _stars;
};

#endif
