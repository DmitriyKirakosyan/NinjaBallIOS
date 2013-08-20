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

CCPoint DrawingController::getLastPoint()
{
    CCPoint lastPoint;
    if (_pathParts != NULL && _pathParts->count() > 0)
    {
        lastPoint = ((CCSprite*) _pathParts->lastObject())->getPosition();
    }
    else if (_startPoint.x != -1 && _startPoint.y != -1)
    {
        lastPoint = _startPoint;
    }
    else
    {
        CCAssert(lastPoint.x != -1 || lastPoint.y != -1, "last point not found");
    }
    return lastPoint;
}

std::vector<CCPoint*> DrawingController::drawPathToPoint(CCPoint point)
{
    
    std::vector<CCPoint*> result;

    CCPoint lastPoint = this->getLastPoint();
    if (_pathParts == NULL)
    {
        _pathParts = new CCArray();
    }
    
    CCPoint* pPartPoint;
    
    CCPoint partPoint;
    CCSprite* pathPart;
    float lineLength = ccpDistance(lastPoint, point);
    for (int i = PATH_DISTANCE; i < lineLength; i+= PATH_DISTANCE) {
        partPoint = ccpLerp(lastPoint, point, (float)i / lineLength);
        pathPart = this->createPathPart(partPoint);
        pathPart->setRotation(-90 - CC_RADIANS_TO_DEGREES(ccpToAngle(ccpSub(partPoint, point))));
        _pathParts->addObject(pathPart);
        _drawingContainer->addChild(pathPart, 0);
        
        //for return
        pPartPoint = new CCPoint();
        pPartPoint->x = partPoint.x;
        pPartPoint->y = partPoint.y;
        result.push_back(pPartPoint);
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
    CCSprite* result = CCSprite::create("track.png");
    result->setPosition(point);
    return result;
}