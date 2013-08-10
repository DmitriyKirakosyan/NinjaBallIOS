//
//  SelectLevelScene.h
//  ninjaBall
//
//  Created by Dmitriy on 8/8/13.
//
//

#ifndef __ninjaBall__SelectLevelScene__
#define __ninjaBall__SelectLevelScene__

#include "cocos2d.h"

class SelectLevelScene : public cocos2d::CCLayer
{
public:
    bool init();
    
    static cocos2d::CCScene* scene();
    
    void closeCallback(cocos2d::CCObject* pSender);
    void playCallback(cocos2d::CCObject* pSender);
    
        
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SelectLevelScene);

};

#endif /* defined(__ninjaBall__SelectLevelScene__) */
