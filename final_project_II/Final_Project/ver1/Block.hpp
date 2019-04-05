//
//  Block.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/12/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include "global.hpp"

class Block {
private:
    float x = WINDOW_WIDTH, y = WINDOW_HEIGHT;
    bool isClicked = false;
    bool isExpanded = false;
    bool isSelected = false;
    int code;
    ALLEGRO_BITMAP *thumbnail = nullptr;
    ALLEGRO_BITMAP *text = nullptr;
    ALLEGRO_BITMAP *pic = nullptr;
    ALLEGRO_COLOR color;
public:
    Block(ALLEGRO_COLOR, int, int);
    ~Block(void);
    void Draw(float, float);
    void ToggleClick(void) { isClicked = !isClicked; }
    void ToggleExpand(void) { isExpanded = !isExpanded; }
    void ToggleSelect(void) { isSelected = !isSelected; }
    float getX(void) { return x; }
    float getY(void) { return y; }
    bool getClicked(void) { return isClicked; }
    bool getExpanded(void) { return isExpanded; }
    bool getSelected(void) { return isSelected; }
    int getCode(void) { return code; }
};

#endif /* Block_hpp */
