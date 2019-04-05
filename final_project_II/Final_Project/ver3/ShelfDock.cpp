//
//  ShelfDock.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "ShelfDock.hpp"

void ShelfDock::Draw(int space)
{
    for (int i = 0; i < space; i ++) {
        al_draw_filled_rounded_rectangle(x + i * d, y, x + i * d + BLOCK_WIDTH, y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, GRAY);
    }
}
