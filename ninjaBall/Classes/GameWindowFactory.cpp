//
//  GameWindowFactory.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#include "GameWindowFactory.h"
#include "AWindow.h"
#include "LevelCompleteWindow.h"
#include "GameScene.h"


const char* GameWindowFactory::LEVEL_COMPLETE_WINDOW = "levelCompleteWindow";

AWindow* GameWindowFactory::getWindow(const char *windowName)
{
    if (windowName == LEVEL_COMPLETE_WINDOW)
    {
        return new LevelCompleteWindow(_gameLayer);
    }
    return NULL;
}