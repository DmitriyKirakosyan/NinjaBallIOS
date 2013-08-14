//
//  Switchable.h
//  ninjaBall
//
//  Created by Dmitriy on 8/14/13.
//
//

#ifndef ninjaBall_Switchable_h
#define ninjaBall_Switchable_h

class SwitchableObject
{
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual bool isOn() = 0;
};


#endif
