//
//  ShelfDock.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef ShelfDock_hpp
#define ShelfDock_hpp

#include "global.hpp"
#include "Card.hpp"

class ShelfDock {
    bool isFormer = true;
    float d = SHELF_W / 4 - BLOCK_WIDTH;
    float x = d / 2;
    float y = (SHELF_H - BLOCK_HEIGHT) / 2;
    
public:
    ShelfDock(void) {}
    ~ShelfDock(void) {}
    
    void Draw(int);
    void SetOnDock(Card &c, bool in) { c.setOnMergerDock(in); }
    
    void ToggleCardSet(void) { isFormer = !isFormer; }
    bool getCardSet(void) { return isFormer; }
};

#endif /* ShelfDock_hpp */
