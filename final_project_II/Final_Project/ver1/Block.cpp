//
//  Block.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/12/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Block.hpp"

Block::Block(ALLEGRO_COLOR block_color, int lv, int i)
{
    char filename[20];
    
    sprintf(filename, "%d-%d text.png", lv, i);
    text = al_load_bitmap(filename);
    
    sprintf(filename, "%d-%d pic.png", lv, i);
    pic = al_load_bitmap(filename);
    
    sprintf(filename, "%d-%d thmb.png", lv, i);
    thumbnail = al_load_bitmap(filename);
    
    color = block_color;
    code = i;
}

Block::~Block(void)
{
    al_destroy_bitmap(text);
    al_destroy_bitmap(pic);
    al_destroy_bitmap(thumbnail);
}

//void Block::ToggleExpand(void)
//{
//    if (isExpanded) isClicked = false;
//    isExpanded = !isExpanded;
//}

void Block::Draw(float draw_x, float draw_y)
{
    x += (draw_x - x) * frames/FPS;
    y += (draw_y - y) * frames/FPS;
    
    if (isExpanded) {
        al_draw_filled_rounded_rectangle(x, y, x + 4.0 * BLOCK_WIDTH, y + 2.0 * BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, color);
        al_draw_bitmap(text, x + 300.0, 2.0 * BLOCK_HEIGHT - 200.0, 0);
        al_draw_bitmap(pic, x + 50.0, y + 50.0, 0);
    } else {
        al_draw_filled_rounded_rectangle(x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, color);
        al_draw_bitmap(thumbnail, x + 30.0, y + 30.0, 0);
        if (isSelected) al_draw_rounded_rectangle(x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, ORANGE_LIGHT, 10.0);
    }
}

