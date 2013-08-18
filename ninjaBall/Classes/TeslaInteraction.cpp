//
//  TeslaInteraction.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/18/13.
//
//

#include "TeslaInteraction.h"
#include "TeslaItem.h"
#include "TeslaSpark.h"
#include "Ninja.h"

using namespace cocos2d;

TeslaInteraction::TeslaInteraction(CCLayer* mapLayer):
_mapLayer(mapLayer)
{
    _teslaItems = new CCArray();
    _sparks = new CCArray();
}

TeslaInteraction::~TeslaInteraction()
{
    this->clear();
    _teslaItems->removeAllObjects();
    _teslaItems->release();
    
    _sparks->removeAllObjects();
    _sparks->release();
}

void TeslaInteraction::clear()
{
    CCObject* spark;
    CCARRAY_FOREACH(_sparks, spark)
    {
        if (_mapLayer->getChildren()->containsObject(spark))
        {
            _mapLayer->removeChild((CCNode*)spark, true);
        }
    }
    _sparks->removeAllObjects();
    _teslaItems->removeAllObjects();
}

void TeslaInteraction::addTeslaItem(TeslaItem *teslaItem)
{
    CCObject* arrayItem;
    TeslaSpark* spark;
    
    CCARRAY_FOREACH(_teslaItems, arrayItem)
    {
        if (teslaItem->getFriendId() ==
            ((TeslaItem*)arrayItem)->getId())
        {
            spark = new TeslaSpark(teslaItem, (TeslaItem*)arrayItem);
            _sparks->addObject(spark);
            _mapLayer->addChild(spark);
        }
    }
    
    _teslaItems->addObject(teslaItem);
}

void TeslaInteraction::interact()
{
    CCObject* arrayItem;
    CCARRAY_FOREACH(_sparks, arrayItem)
    {
        ((TeslaSpark*)arrayItem)->update();
    }
}

bool TeslaInteraction::checkDamage(Ninja* ninja)
{
    bool result = false;
    CCObject* arrayItem;
    CCARRAY_FOREACH(_sparks, arrayItem)
    {
        if (((TeslaSpark*)arrayItem)->checkHit(ninja))
        {
            result = true;
            break;
        }
    }
    return result;
}