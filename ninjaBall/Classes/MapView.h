//
//  MapView.h
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#ifndef __ninjaBall__MapView__
#define __ninjaBall__MapView__

#include "cocos2d.h"
#include "World.h"

class ObstaclesController;
class Ninja;
class FinishLine;

class MapView : public cocos2d::CCLayer, public World
{
public:
    MapView(Ninja* ninja);
    inline ObstaclesController* getObstaclesController() { return _obstacles; }
    
    /**
     Создает уровень из json файла
     */
    void createLevel(const char* fileName);
    
    /**
     ограничивает путь стенами и возвращает точку,
     наиболее близкую к endPoint и ограниченную стеной
     */
    cocos2d::CCPoint restrictPath(cocos2d::CCPoint startPoint, cocos2d::CCPoint endPoint);
    
    /**
     Очищает сцену от объектов карты
     */
    void clear();
    
    void tick();
    
    /**
     Проверяет, выиграл ли нинзя
     @param ninja нинзя
     TODO странный метод, зачем ему параметр?
     */
    bool isNinjaWin(cocos2d::CCSprite* ninja);
    
    //world interface
    inline Ninja* getHero() { return _ninja; }
  
private:
    ObstaclesController* _obstacles;
    FinishLine* _finishLine;
    Ninja* _ninja;
};

#endif /* defined(__ninjaBall__MapView__) */
