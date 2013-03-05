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

class ObstaclesController;
class Ninja;

class MapView : public cocos2d::CCLayer
{
public:
    MapView(cocos2d::CCSize winSize, Ninja* ninja);
    inline ObstaclesController* getObstacles() { return _obstacles; }
    
    /**
     Создает тестовый уровень
     */
    void createTestLevel();
    
    /**
     Создает уровень из json файла
     */
    void createLevel(const char* fileName);
    
    /**
     Очищает сцену от объектов карты
     */
    void clear();
    
    /**
     Проверяет, выиграл ли нинзя
     @param ninja нинзя
     */
    bool isNinjaWin(cocos2d::CCSprite* ninja);
  
private:
    ObstaclesController* _obstacles;
    cocos2d::CCSprite* _finishLine;
    Ninja* _ninja;
    
    cocos2d::CCSize _winSize;
};

#endif /* defined(__ninjaBall__MapView__) */
