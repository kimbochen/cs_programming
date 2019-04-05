//
//  Merger.cpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#include "Merger.hpp"

Merger::Merger(void)
{
    lf_x = 600.0;
    lf_y = 20.0;
    
    rt_x = (3 * WINDOW_WIDTH - lf_x) / 4 - BLOCK_WIDTH / 2;
    rt_y = lf_y;
    
    plus_sign = al_load_bitmap("plus_sign.jpg");
    sign_x = (WINDOW_WIDTH + lf_x) / 2 - al_get_bitmap_width(plus_sign);
    sign_y = lf_y;
}

Merger::~Merger(void)
{
    al_destroy_bitmap(plus_sign);
}

void Merger::DrawMerger(void)
{
    al_draw_filled_rounded_rectangle(lf_x, lf_y, lf_x + BLOCK_WIDTH, lf_y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, ORANGE_LIGHT);
    al_draw_filled_rounded_rectangle(rt_x, rt_y, rt_x + BLOCK_WIDTH, rt_y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, ORANGE_LIGHT);
    al_draw_bitmap(plus_sign, sign_x, sign_y, 0);
}

void Merger::CardHover(void)
{
    
}
