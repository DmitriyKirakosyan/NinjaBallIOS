//
//  Door.cpp
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#include "Door.h"


void Door::open()
{
    _opened = true;
}

void Door::close()
{
    _opened = false;
}