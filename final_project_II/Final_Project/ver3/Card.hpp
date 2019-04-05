//
//  Card.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

//#include "global.hpp"
#include "Main.hpp"

class Card {
    float x, y;
    bool isClicked = false;
    bool isHovered = false;
    bool onMDock = false;
    bool onSDock = true;
    int code;
    ALLEGRO_BITMAP *thumbnail = nullptr;
    ALLEGRO_BITMAP *text = nullptr;
    ALLEGRO_BITMAP *pic = nullptr;
    
public:
    Card(int);
    ~Card(void);
    
    Card(void) {}
    void DrawThmb(void);
    void DrawInfo(void);
    
    float getX(void) { return x; }
    float getY(void) { return y; }
    bool getClick(void) { return isClicked; }
    bool getHover(void) { return isHovered; }
    bool getOnMergerDock(void) { return onMDock; }
    bool getOnShelfDock(void) { return onSDock; }
    int getCode(void) { return code; }
//    ALLEGRO_BITMAP *getThmb(void) { return thumbnail;}
//    ALLEGRO_BITMAP *getPic(void);
//    ALLEGRO_BITMAP *getText(void);
    
    void setHover(bool in) { isHovered = in; }
    void ToggleClick(void) { isClicked = !isClicked; }
    void setPos(float, float);
    void setOnMergerDock(bool in) { onMDock = in; }
    void setOnShelfDock(bool in) { onSDock = in; }
};

#endif /* Card_hpp */
