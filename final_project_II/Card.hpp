//
//  Card.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/21/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include "Main.hpp"

typedef enum { SHELF, DOCK } CARD_STATE;

class Card {
    int code;
    bool click = false, hover = false;
    float x, y;
    CARD_STATE state;
    
public:
    Card(int);
    ~Card(void);
    
    void checkClick(float, float);
    void checkHover(float, float);
    void setPos(float, float);
    void moveTo(CARD_STATE in_state) { state = in_state; }
    
    CARD_STATE getState(void) { return state; }
    bool getClick(void) { return click; }
    bool getHover(void) { return hover; }
    int getCode(void) { return code; }
};

#endif /* Card_hpp */
