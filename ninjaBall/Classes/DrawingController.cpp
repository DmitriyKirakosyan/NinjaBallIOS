//
//  DrawingController.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/13/13.
//
//

#include "DrawingController.h"

using namespace cocos2d;

DrawingController::DrawingController(CCLayer* drawingLayer)
{
    _drawingContainer = drawingLayer;
    _pathParts = NULL;
}

void DrawingController::drawPathToPoint(CCPoint point)
{
    
    CCPoint lastPoint;
    if (_pathParts != NULL && _pathParts->count() > 0)
    {
        lastPoint = ((CCSprite*) _pathParts->lastObject())->getPosition();
    }
    else if (_startPoint.x != -1 && _startPoint.y != -1)
    {
        lastPoint = _startPoint;
        _pathParts = new CCArray();
    }
    else
    {
        CCLOGERROR("[ERROR] cant find last point!");
        return;
    }
    
    CCSprite* pathPart;
    float lineLength = ccpDistance(lastPoint, point);
    CCLog("last point : %f, %f", lastPoint.x, lastPoint.y);
    CCLog("now point : %f, %f", point.x, point.y);
    for (int i = PATH_DISTANCE; i < lineLength; i+= PATH_DISTANCE) {
        CCLog("coef for interpolation %f", ((float)i / lineLength));
        pathPart = this->createPathPart(ccpLerp(lastPoint, point, (float)i / lineLength));
        _pathParts->addObject(pathPart);
        _drawingContainer->addChild(pathPart);
    }
    
}

void DrawingController::clear()
{
    if (_pathParts != NULL && _pathParts->count() > 0)
    {
        CCObject* pathPart;
        CCARRAY_FOREACH(_pathParts, pathPart)
        {
            _drawingContainer->removeChild((CCSprite*) pathPart, true);
        }
        _pathParts->removeAllObjects();
    }
    _pathParts = NULL;
}

void DrawingController::removePathPartByPoint(CCPoint point)
{
    CCObject* item;
    CCSprite* pathPart;
    CCARRAY_FOREACH(_pathParts, item)
    {
        pathPart = (CCSprite*) item;
        if (pathPart->getPosition().x == point.x && pathPart->getPosition().y == point.y)
        {
            _pathParts->removeObject(pathPart);
            _drawingContainer->removeChild(pathPart, true);
            break;
        }
    }
}

void DrawingController::setStartPoint(CCPoint point)
{
    _startPoint = point;
}

CCSprite* DrawingController::createPathPart(CCPoint point)
{
    CCSprite* result = CCSprite::create("footprint.png");
    result->setPosition(point);
    return result;
}