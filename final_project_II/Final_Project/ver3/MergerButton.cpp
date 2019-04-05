//
//  MergerButton.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "MergerButton.hpp"

bool MergerButton::isHovered(float ms_x, float ms_y)
{
    return (SHELF_W <= ms_x && ms_x <= WINDOW_WIDTH &&
            VIEWER_H / 2 <= ms_y && ms_y <= VIEWER_H);
}

void MergerButton::checkClick(float ms_x, float ms_y)
{
    isClicked = isHovered(ms_x, ms_y);
}
