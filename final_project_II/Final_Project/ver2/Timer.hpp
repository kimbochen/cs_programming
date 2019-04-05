//
//  Timer.hpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#ifndef Timer_hpp
#define Timer_hpp

#include "global.hpp"

class Timer {
    float x, y;
    int timelength = 60;
    int penalty = 5;
    bool isDone = false;
    
public:
    Timer(float in_x, float in_y): x(in_x), y(in_y) {}
    ~Timer(void);
    void DrawTimer(void);
    void Countdown(void);
    void CutTime(void);
    bool getDone(void) { return isDone; }
};

#endif /* Timer_hpp */
