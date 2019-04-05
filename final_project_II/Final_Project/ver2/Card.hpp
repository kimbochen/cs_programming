//
//  Card.hpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#ifndef Card_hpp
#define Card_hpp

#include "global.hpp"

class Card {
    int code;
    float x, y;
    
    ALLEGRO_BITMAP *pic = nullptr;
    ALLEGRO_BITMAP *text = nullptr;
    ALLEGRO_BITMAP *thmb = nullptr;
    
    bool isDisplayed = false;
    bool isClicked = false;
    bool isHovered = false;
    
public:
    Card(float, float, int);
    ~Card(void);
    void ToggleDisplay(void) { isDisplayed = !isDisplayed; }
    void ToggleHover(void) { isHovered = !isHovered; }
    void ToggleClick(void) { isClicked = !isClicked; }
    float getX(void) { return x; }
    float getY(void) { return y; }
    void DrawCard(void);
    void UpdateXY(float, float);
};

#endif /* Card_hpp */
