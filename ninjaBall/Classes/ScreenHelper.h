//
//  ScreenHelper.h
//  ninjaBall
//
//  Created by Dmitriy on 8/9/13.
//
//

#ifndef ninjaBall_ScreenHelper_h
#define ninjaBall_ScreenHelper_h

#include "cocos2d.h"
#include "Settings.h"

using namespace cocos2d;

class ScreenHelper {
public:
    static CCPoint convetGLtoVirtual(CCPoint point) {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        size.width -= Settings::REAL_WIDTH_OFFSET * 2;
        size.height -= Settings::REAL_HEIGHT_OFFSET * 2;
        
        point.x -= Settings::REAL_WIDTH_OFFSET;
        point.y -= Settings::REAL_HEIGHT_OFFSET;
        
        float widthCoef = Settings::VIRTUAL_WIDTH / size.width;
        float heightCoef = Settings::VIRTUAL_HEIGHT / size.height;
        CCPoint result = ccp(point.x * widthCoef, point.y * heightCoef);
        return result;
    }
};


#endif
