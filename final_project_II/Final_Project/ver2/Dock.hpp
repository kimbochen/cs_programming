//
//  Dock.hpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#ifndef Dock_hpp
#define Dock_hpp

#include "global.hpp"
#include "Card.hpp"

class Dock {
    std::vector<Card *> CardSet;
    
    float button_x, button_y;
    int start = 1;
    
    bool isDrag = false;
    bool isRotate = false;
    bool buttonClick = false;
    
    ALLEGRO_BITMAP *button = nullptr;
    
public:
    Dock(void);
    ~Dock(void) {}
    void DrawDock(void);
    void MouseHover(float, float);
    void MouseClick(float, float);
    void AddCard(Card *);
};


#endif /* Dock_hpp */
