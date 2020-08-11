//
//  WindowManager.h
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#ifndef __ninjaBall__WindowManager__
#define __ninjaBall__WindowManager__

#include "cocos2d.h"

class AWindowFactory;
class AWindow;
class AWindowParams;

class WindowManager : public cocos2d::CCLayer
{
public:
    WindowManager(cocos2d::CCLayer* layer, AWindowFactory* windowFactory);
    
    void showWindow(const char* windowName);
    void showWindow(const char* windowName, AWindowParams& windowParams);
    
private:
    
    void update();
    
    AWindowFactory* _windowFactory;
    AWindow* _currentWindow;
    
    const int WINDOW_Z_ORDER;
    
};

#endif /* defined(__ninjaBall__WindowManager__) */
