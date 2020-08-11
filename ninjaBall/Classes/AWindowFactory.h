//
//  AWindowFactory.h
//  ninjaBall
//
//  Created by Dmitriy on 2/24/13.
//
//

#ifndef __ninjaBall__AWindowFactory__
#define __ninjaBall__AWindowFactory__

class AWindow;

class AWindowFactory
{
public:
    virtual AWindow* getWindow(const char* windowName) = 0;
};

#endif /* defined(__ninjaBall__AWindowFactory__) */
