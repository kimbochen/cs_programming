//
//  MergerDock.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef MergerDock_hpp
#define MergerDock_hpp

#include "global.hpp"
#include "Card.hpp"

class MergerDock {
    int space = 0;
    bool hide = false;
    float x1 = SHELF_W / 4 - BLOCK_WIDTH / 2;
    float y = (VIEWER_H - BLOCK_HEIGHT) / 2;
    float x2 = SHELF_W * 3/4 - BLOCK_WIDTH / 2;
public:
    MergerDock(void) {}
    ~MergerDock(void) {}
    
    void Draw(void);
    void SetDestin(Card &);
    void SetOnDock(Card &, bool);
    
    int getSpace(void) { return space; }
    
    void setHide(bool in) { hide = in; }
    void setSpace(int in) { space = in; }
};

#endif /* MergerDock_hpp */
