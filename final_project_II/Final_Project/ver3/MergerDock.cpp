//
//  MergerDock.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "MergerDock.hpp"

void MergerDock::Draw(void)
{
    if (hide) return;
    
//    float margin;
    
    al_draw_filled_rounded_rectangle(x1, y, x1 + BLOCK_WIDTH, y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
//    margin = (BLOCK_WIDTH - al_get_bitmap_width(c1.getThmb())) / 2;
    
    al_draw_filled_rounded_rectangle(x2, y, x2 + BLOCK_WIDTH, y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
//    margin = (BLOCK_WIDTH - al_get_bitmap_width(c2.getThmb())) / 2;
}

void MergerDock::SetDestin(Card &c)
{
    if (space == 0)
        c.setPos(x1, y);
    else if (space == 1)
        c.setPos(x2, y);
    else
        puts("MergerDock: space count malfunction");
}

void MergerDock::SetOnDock(Card &c, bool onDock)
{
    c.setOnMergerDock(onDock);
}
