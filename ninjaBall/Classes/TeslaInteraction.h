//
//  TeslaInteraction.h
//  ninjaBall
//
//  Created by Dmitriy on 8/18/13.
//
//

#ifndef __ninjaBall__TeslaInteraction__
#define __ninjaBall__TeslaInteraction__

#include "cocos2d.h"

class TeslaItem;
class Ninja;

class TeslaInteraction
{
public:
    TeslaInteraction(cocos2d::CCLayer* mapLayer);
    ~TeslaInteraction();
    
    void clear();
    
    void interact();
    
    bool checkDamage(Ninja* ninja);
    
    void addTeslaItem(TeslaItem* teslaItem);
    
private:
    cocos2d::CCLayer* _mapLayer;
    
    cocos2d::CCArray* _teslaItems;
    cocos2d::CCArray* _sparks;
};

#endif /* defined(__ninjaBall__TeslaInteraction__) */
