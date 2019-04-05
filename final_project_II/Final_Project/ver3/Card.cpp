//
//  Card.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Card.hpp"

Card::Card(int in_code)
{
    char filename[20];
    
    sprintf(filename, "1-%d text.png", in_code);
    text = al_load_bitmap(filename);
    
    sprintf(filename, "1-%d pic.png", in_code);
    pic = al_load_bitmap(filename);
    
    sprintf(filename, "1-%d thmb.png", in_code);
    thumbnail = al_load_bitmap(filename);
    
    code = in_code;
}

Card::~Card(void)
{
    al_destroy_bitmap(text);
    al_destroy_bitmap(pic);
    al_destroy_bitmap(thumbnail);
}

void Card::DrawThmb(void)
{
    float w, h;
    
    w = al_get_bitmap_width(thumbnail);
    h = al_get_bitmap_height(thumbnail);
    al_draw_bitmap(thumbnail, x, y, 0);
//    al_draw_bitmap(thumbnail, x + (BLOCK_WIDTH - w) / 2, y + (BLOCK_HEIGHT - h) / 2, 0);
    al_draw_bitmap(thumbnail, x + (CARD_W - w) / 2, y + (CARD_H - h) / 2, 0);
}

void Card::DrawInfo(void)
{
    float w1, h1, w2, h2;
    w1 = al_get_bitmap_width(pic);
    h1 = al_get_bitmap_height(pic);
    
    w2 = al_get_bitmap_width(text);
    h2 = al_get_bitmap_height(text);
    
    al_draw_bitmap(pic, (SHELF_W - w1) / 2, (SHELF_H - h1 - h2) / 3, 0);
    al_draw_bitmap(text, (SHELF_W - w2) / 2, SHELF_H - (SHELF_H - h1 - h2) / 3, 0);
}

void Card::setPos(float in_x, float in_y)
{
    x = in_x;
    y = in_y;
}
