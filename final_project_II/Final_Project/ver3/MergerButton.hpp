//
//  MergerButton.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef MergerButton_hpp
#define MergerButton_hpp

#include "global.hpp"

class MergerButton {
    bool isClicked = false;
    bool hide = true;
    
public:
    MergerButton(void) {}
    ~MergerButton(void) {}
    
    void Draw(void);
    bool isHovered(float, float);
    void checkClick(float, float);
    
    bool getClick(void) { return isClicked; }
    
    void setHide(bool in) { hide = in; }
};

#endif /* MergerButton_hpp */
