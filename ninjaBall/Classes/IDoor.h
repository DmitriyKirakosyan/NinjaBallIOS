//
//  IDoor.h
//  ninjaBall
//
//  Created by Dmitriy on 8/12/13.
//
//

#ifndef ninjaBall_IDoor_h
#define ninjaBall_IDoor_h

class IDoor {
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool isOpened() = 0;
};

#endif
