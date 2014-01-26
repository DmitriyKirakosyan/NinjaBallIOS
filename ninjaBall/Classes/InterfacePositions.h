//
//  InterfacePositions.h
//  ninjaBall
//
//  Created by Dmitriy on 8/13/13.
//
//

#ifndef ninjaBall_InterfacePositions_h
#define ninjaBall_InterfacePositions_h

#include "Settings.h"

class InterfacePositions
{
public:
    
    static const int VIRTUAL_HEIGHT = 640; //copy form Settings::VIRTUAL_HEIGHT
    
    //main menu
    static const int MENU_PLAY_BTN_X = 282;
    static const int MENU_PLAY_BTN_Y = VIRTUAL_HEIGHT-273;
    static const int MENU_OPTIONS_BTN_X = 282;
    static const int MENU_OPTIONS_BTN_Y = VIRTUAL_HEIGHT-413;
    static const int MENU_ABOUT_BTN_X = 283;
    static const int MENU_ABOUT_BTN_Y = VIRTUAL_HEIGHT-553;
    
    //level selection
    static const int LEVEL_SELECT_ITEM_Y_OFFSET = 168;
    static const int LEVEL_SELECT_ITEM_Y_START = VIRTUAL_HEIGHT - 180;
    
    //level complete window
    static const int LEVEL_COMPLETE_NEXTLVL_X = 188;
    static const int LEVEL_COMPLETE_NEXTLVL_Y = VIRTUAL_HEIGHT-390;
    static const int LEVEL_COMPLETE_REPLAY_X = 20;
    static const int LEVEL_COMPLETE_REPLAY_Y = VIRTUAL_HEIGHT-504;
    static const int LEVEL_COMPLETE_TOMENU_X = 351;
    static const int LEVEL_COMPLETE_TOMENU_Y = VIRTUAL_HEIGHT-504;
    static const int LEVEL_COMPLETE_STAR_Y = VIRTUAL_HEIGHT-267;
    static const int LEVEL_COMPLETE_CUP_X = 82;
    static const int LEVEL_COMPLETE_CUP_Y = VIRTUAL_HEIGHT-129;
    static const int LEVEL_COMPLETE_CIRCLE_X = 300;
    static const int LEVEL_COMPLETE_CIRCLE_Y = VIRTUAL_HEIGHT-417;
    static const int LEVEL_COMPLETE_SHADOW_CIRCLE_X = 300;
    static const int LEVEL_COMPLETE_SHADOW_CIRCLE_Y = VIRTUAL_HEIGHT-574;

};


#endif
