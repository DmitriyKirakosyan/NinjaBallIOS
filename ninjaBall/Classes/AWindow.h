//
//  AWindow.h
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#ifndef ninjaBall_AWindow_h
#define ninjaBall_AWindow_h

#include "cocos2d.h"

class AWindowParams;

class AWindow : public cocos2d::CCSprite
{
public:
    AWindow()
    {
        _readyToClose = false;
    };
    
    virtual void close()
    {
        _readyToClose = true;
    }
    
    virtual void open()
    {
        _readyToClose = false;
    }
    
    virtual void open(AWindowParams& windowParams) = 0;
    
    /**
     Когда окно готово к закрытию, функция возвращает true
     и виндоу менеджер закрывает окно
     */
    virtual bool readyToClose()
    {
        return _readyToClose;
    }
    
private:
    bool _readyToClose;
    
protected:
    inline void setReadyToClose(bool value) { _readyToClose = value; }
};


#endif
