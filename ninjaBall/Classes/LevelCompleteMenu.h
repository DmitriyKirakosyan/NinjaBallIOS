//
//  LevelCompleteMenu.h
//  ninjaBall
//
//  Created by Dmitriy on 3/3/13.
//
//

#ifndef ninjaBall_LevelCompleteMenu_h
#define ninjaBall_LevelCompleteMenu_h

class LevelCompleteMenu
{
public:
    virtual void nextLevel() = 0;
    virtual void replyLevel() = 0;
    virtual void returnToMainMenu() = 0;
    virtual bool canStartNextLevel() = 0;
};


#endif
