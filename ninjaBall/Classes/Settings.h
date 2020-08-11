//
//  Settings.h
//  ninjaBall
//
//  Created by Dmitriy on 8/8/13.
//
//

#ifndef ninjaBall_Settings_h
#define ninjaBall_Settings_h

#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#define MAX(x,y) (((x) < (y)) ? (y) : (x))



class Settings {
public:
    static const int TILED_MAP_WIDTH;
    static const int TILED_MAP_HEIGHT;
    
    static const int VIRTUAL_WIDTH = 1136;
    static const int VIRTUAL_HEIGHT = 640;
    
    static const int VIRTUAL_GAME_WIDTH = 1072;
    static const int VIRTUAL_GAME_HEIGHT = 578;
    
    static float FULL_VIRTUAL_WIDTH;
    static float FULL_VIRTUAL_HEIGHT;
    
    static float REAL_WIDTH_OFFSET;
    static float REAL_HEIGHT_OFFSET;
    
    static float density;
    
    static void createDensity(float realWidth, float realHeight) {
        float widthCoef = realWidth / VIRTUAL_WIDTH;
        float heightCoef = realHeight / VIRTUAL_HEIGHT;
        float minCoef = MIN(widthCoef, heightCoef);
        Settings::density = minCoef;
        initFullDimenstions(realWidth, realHeight);
    }
    
private:
    static void initFullDimenstions(float realWidth, float realHeight) {
        //float coef = MAX(VIRTUAL_WIDTH / realWidth, VIRTUAL_HEIGHT / realHeight);
        FULL_VIRTUAL_WIDTH = realWidth * 1/Settings::density;
        FULL_VIRTUAL_HEIGHT = realHeight * 1/Settings::density;
        REAL_WIDTH_OFFSET = -(VIRTUAL_WIDTH - FULL_VIRTUAL_WIDTH) / 2 * Settings::density;
        REAL_HEIGHT_OFFSET = -(VIRTUAL_HEIGHT - FULL_VIRTUAL_HEIGHT) / 2 * Settings::density;
    }

};


#endif
