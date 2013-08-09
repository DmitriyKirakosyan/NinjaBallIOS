//
//  WindowManager.cpp
//  ninjaBall 
//
//  Created by Dmitriy on 2/24/13.
//
//

#include "WindowManager.h"
#include "AWindowFactory.h"
#include "AWindow.h"
#include "LevelCompleteWindow.h"
#include "Settings.h"

using namespace cocos2d;


WindowManager::WindowManager(CCLayer* layer, AWindowFactory* windowFactory):WINDOW_Z_ORDER(10)
{
    CCAssert(layer != NULL, "layer is NULL");
    CCAssert(windowFactory != NULL, "window factory is NULL");
    _currentWindow = NULL;
    _windowFactory = windowFactory;
    this->schedule(schedule_selector(WindowManager::update));
}

void WindowManager::showWindow(const char *windowName)
{
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _currentWindow = _windowFactory->getWindow(windowName);
    _currentWindow->setPosition(ccp(Settings::VIRTUAL_WIDTH/2, Settings::VIRTUAL_HEIGHT/2));
    
    this->addChild(_currentWindow, WINDOW_Z_ORDER);
    _currentWindow->open();
}

void WindowManager::update()
{
    if (_currentWindow != NULL)
    {
        if (_currentWindow->readyToClose())
        {
            _currentWindow->close();
            this->removeChild(_currentWindow, false);
        }
    }
}
