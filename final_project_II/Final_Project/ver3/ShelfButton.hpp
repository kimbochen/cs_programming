//
//  ShelfButton.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef ShelfButton_hpp
#define ShelfButton_hpp

#include "global.hpp"

class ShelfButton {
    bool isClicked = false;
    bool hide = true;
    
public:
    ShelfButton(void) {}
    ~ShelfButton(void) {}
    
    bool isHovered(float, float);
    void checkClick(float, float);
    
    bool getClick(void) { return isClicked; }
    
    void setHide(bool in) { hide = in; }
};

#endif /* ShelfButton_hpp */
