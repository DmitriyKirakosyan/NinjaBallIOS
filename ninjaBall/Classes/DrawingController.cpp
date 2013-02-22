//
//  DrawingController.cpp
//  ninjaBall
//
//  Created by Dmitriy on 2/13/13.
//
//

#include "DrawingController.h"

using namespace cocos2d;

DrawingController::DrawingController(CCLayer* drawingLayer):PATH_DISTANCE(60)
{
    _drawingContainer = drawingLayer;
    _pathParts = NULL;
}

CCArray* DrawingController::drawPathToPoint(CCPoint point)
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
        return NULL;
    }
    
    CCArray* result = CCArray::create();
    CCPoint* pPartPoint;
    
    CCPoint partPoint;
    CCSprite* pathPart;
    float lineLength = ccpDistance(lastPoint, point);
    for (int i = PATH_DISTANCE; i < lineLength; i+= PATH_DISTANCE) {
        partPoint = ccpLerp(lastPoint, point, (float)i / lineLength);
        pathPart = this->createPathPart(partPoint);
        _pathParts->addObject(pathPart);
        _drawingContainer->addChild(pathPart, 0);
        
        //for return
        pPartPoint = new CCPoint();
        pPartPoint->x = partPoint.x;
        pPartPoint->y = partPoint.y;
        pPartPoint->autorelease();
        result->addObject(pPartPoint);
    }
    
    return result;
}

void DrawingController::stopDraw()
{
    if (_pathParts != NULL && _pathParts->count() > 0)
    {
        CCSprite* pathPart = (CCSprite*) _pathParts->lastObject();
        pathPart->setScale(1.2);
    }
}

void DrawingController::clear()
{
    if (_pathParts != NULL && _pathParts->count() > 0)
    {
        CCObject* pathPart;
        CCARRAY_FOREACH(_pathParts, pathPart)
        {
            if (_drawingContainer->getChildren()->containsObject(pathPart))
            {
                _drawingContainer->removeChild((CCSprite*) pathPart, false);
            }
        }
        while (_pathParts->count() > 0)
        {
            _pathParts->removeLastObject();
        }
    }
    _pathParts = NULL;
}

void DrawingController::removePathPartByPointFromScreen(CCPoint point)
{
    CCObject* item;
    CCSprite* pathPart;
    CCARRAY_FOREACH(_pathParts, item)
    {
        pathPart = (CCSprite*) item;
        if (pathPart->getPosition().x == point.x && pathPart->getPosition().y == point.y)
        {
            _drawingContainer->removeChild(pathPart, true);
            break;
        }
    }
}

void DrawingController::removeOldestPathPartFromScreen()
{
    CCSprite* pathPart = (CCSprite*) _pathParts->objectAtIndex(0);
    _drawingContainer->removeChild(pathPart, true);
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