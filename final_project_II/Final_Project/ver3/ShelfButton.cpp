//
//  ShelfButton.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "ShelfButton.hpp"

bool ShelfButton::isHovered(float ms_x, float ms_y)
{
    return (SHELF_W <= ms_x && ms_x <= WINDOW_WIDTH &&
            VIEWER_H <= ms_y && ms_y <= WINDOW_HEIGHT);
}

void ShelfButton::checkClick(float ms_x, float ms_y)
{
    isClicked = isHovered(ms_x, ms_y);
}
