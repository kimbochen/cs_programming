//
//  Viewer.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Viewer_hpp
#define Viewer_hpp

#include "global.hpp"

class Viewer {
    bool hide = true;
    
public:
    Viewer(void) {}
    ~Viewer(void) {}
    
    void displayCard(void);
    
    void setHide(bool in){ hide = in; }
};

#endif /* Viewer_hpp */
