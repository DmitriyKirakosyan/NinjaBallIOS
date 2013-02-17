//
//  DrawingController.h
//  ninjaBall
//
//  Created by Dmitriy on 2/13/13.
//
//

#ifndef __ninjaBall__DrawingController__
#define __ninjaBall__DrawingController__

#include "cocos2d.h"


class DrawingController
{
public:
    DrawingController(cocos2d::CCLayer* drawingLayer);
    
    /**
     Удаляет нарисованный путь со сцены
     */
    void clear();
    
    /**
     Удаляет часть нарисованного пути по заданной точке
     */
    void removePathPartByPoint(cocos2d::CCPoint point);
    
    /**
     Рисует путь от последней до заданной точки
     */
    void drawPathToPoint(cocos2d::CCPoint point);
    
    /**
     Устанавливает начальную точку для рисования пути
     */
    void setStartPoint(cocos2d::CCPoint point);
    
private:
    const float PATH_DISTANCE = 60;
    
    cocos2d::CCArray* _pathParts;
    cocos2d::CCArray* _pathPartsCollector;
    cocos2d::CCLayer* _drawingContainer;
    
    cocos2d::CCPoint _startPoint;
    
    cocos2d::CCSprite* createPathPart(cocos2d::CCPoint point);
    
};

#endif /* defined(__ninjaBall__DrawingController__) */
