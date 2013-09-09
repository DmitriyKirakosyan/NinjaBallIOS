//
//  LevelCompleteWindowParams.h
//  ninjaBall
//
//  Created by Dmitriy on 8/21/13.
//
//

#ifndef ninjaBall_LevelCompleteWindowParams_h
#define ninjaBall_LevelCompleteWindowParams_h

#include "AWindowParams.h"

class LevelCompleteWindowParams : public AWindowParams
{
public:
    LevelCompleteWindowParams(float seconds):seconds(seconds){}
    
    virtual int getType() { return AWindowParams::LEVEL_COMPLETE_PARAMS; }
    
    float seconds;
};

#endif
