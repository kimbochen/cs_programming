//
//  Viewer.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Viewer.hpp"

void Viewer::displayCard(void)
{
    if (!hide)
        al_draw_filled_rounded_rectangle(0.0, 0.0, SHELF_W, SHELF_H, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
}
