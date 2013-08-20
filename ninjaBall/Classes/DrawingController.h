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
     Удаляет часть нарисованного пути по заданной точке только с экрана,
     в массиве она остается
     */
    void removePathPartByPointFromScreen(cocos2d::CCPoint point);
    
    /**
     Удаляет самую старую часть нарисованного пути только с экрана,
     в массиве она остается
     */
    void removeOldestPathPartFromScreen();
    
    cocos2d::CCPoint getLastPoint();
    
    /**
     Рисует путь от последней до заданной точки
     @arg point
     @return массив построенных точек пути
     */
    std::vector<cocos2d::CCPoint*> drawPathToPoint(cocos2d::CCPoint point);
    
    void stopDraw();
    
    /**
     Устанавливает начальную точку для рисования пути
     */
    void setStartPoint(cocos2d::CCPoint point);
    
private:
    const float PATH_DISTANCE;
    
    cocos2d::CCArray* _pathParts;
    //cocos2d::CCArray* _pathPartsCollector;
    cocos2d::CCLayer* _drawingContainer;
    
    cocos2d::CCPoint _startPoint;
    
    cocos2d::CCSprite* createPathPart(cocos2d::CCPoint point);
    
};

#endif /* defined(__ninjaBall__DrawingController__) */
