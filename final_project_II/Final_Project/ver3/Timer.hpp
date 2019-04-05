//
//  Timer.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include "global.hpp"
//#include "Main.hpp"

class Timer {
    int tlen;
    char text[3];
    bool timerEnd = false;
    float x = (WINDOW_WIDTH - MENU_W) / 2, y = WINDOW_HEIGHT - VIEWER_H / 2;
public:
    Timer(int in): tlen(in) {}
    ~Timer(void) {}
    
    void Reset(void) { tlen = 60; }
    void Draw(ALLEGRO_FONT *);
    void Countdown(void);
    void Penalty(void) { tlen -= 10; }
    int getTime(void) { return tlen; }
    bool getTimerEnd(void) { return timerEnd; }
};

#endif /* Timer_hpp */
