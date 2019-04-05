//
//  Dock.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/21/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Dock_hpp
#define Dock_hpp

#include "Main.hpp"

class Dock {
    int space = 0;
    
public:
    int getSpace(void) { return space; }
    void occupy(void) { space ++; }
    void pop(void) { space --; }
};

#endif /* Dock_hpp */
