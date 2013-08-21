//
//  LevelProvider.h
//  ninjaBall
//
//  Created by Dmitriy on 8/11/13.
//
//

#ifndef ninjaBall_LevelProvider_h
#define ninjaBall_LevelProvider_h

#include "cocos2d.h"

class LevelProvider
{
public:
    
    static LevelProvider* getInstance()
    {
        if (_instance == NULL) { _instance = new LevelProvider(); }
        return _instance;
    }
    
    LevelProvider();
    
    bool hasNextLevel(const char* currentLevel);
    bool isLevelAvailable(const char* level);
    const char* getNextLevel(const char* currentLevel);
    void completeLevel(const char* level);
    
    inline int getAvailableLevelsNum() { return _availableLevelsNum; }
    
    static const int LEVELS_NUM = 3;
    const char* LEVELS[3];
    
    
    
private:
    static const char* AVAILABLE_LEVELS_NUM_KEY;
    static LevelProvider* _instance;
    int _availableLevelsNum;
};

#endif