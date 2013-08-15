//
//  LevelProvider.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/11/13.
//
//

#include "LevelProvider.h"
#include <iostream.h>
#include "cocos2d.h"

using namespace cocos2d;

LevelProvider* LevelProvider::_instance = NULL;
const char* LevelProvider::AVAILABLE_LEVELS_NUM_KEY = "available_levels_num";

LevelProvider::LevelProvider()
{
    CCUserDefault* userData = CCUserDefault::sharedUserDefault();
    int storedValue = userData->getIntegerForKey(AVAILABLE_LEVELS_NUM_KEY);
    
    CCLog("stored value : %d", storedValue);
    
    _availableLevelsNum = storedValue == 0 ? 1 : storedValue;
    LEVELS[0] = "level_1.json";
    LEVELS[1] = "level_2.json";
    LEVELS[2] = "level_3.json";
}


bool LevelProvider::hasNextLevel(const char* currentLevel)
{
    return std::strcmp(LEVELS[LEVELS_NUM-1], currentLevel) != 0;
}

bool LevelProvider::isLevelAvailable(const char* level)
{
    bool result = false;
    for (int i = 0; i < _availableLevelsNum; ++i)
    {
        if (std::strcmp(LEVELS[i], level) == 0)
        {
            result = true;
            break;
        }
    }
    return result;
}

void LevelProvider::completeLevel(const char *level)
{
    if (this->hasNextLevel(level)) {
        _availableLevelsNum++;
        
        CCUserDefault* userData = CCUserDefault::sharedUserDefault();
        userData->setIntegerForKey(AVAILABLE_LEVELS_NUM_KEY, _availableLevelsNum);
        userData->flush();
    }
}

const char* LevelProvider::getNextLevel(const char* currentLevel)
{
    const char* result;
    for (int i = 0; i < _availableLevelsNum; ++i)
    {
        if (std::strcmp(LEVELS[i], currentLevel) == 0)
        {
            CCLog("levels : %s, %s", LEVELS[i], currentLevel);
            result = LEVELS[i+1];
            break;
        }
    }
    return result;
}

