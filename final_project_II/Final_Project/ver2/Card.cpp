//
//  Card.cpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#include "Card.hpp"

Card::Card(float in_x, float in_y, int in_code)
{
    char filename[20];
    
    sprintf(filename, "1-%d text.png", in_code);
    text = al_load_bitmap(filename);
    
    sprintf(filename, "1-%d pic.png", in_code);
    pic = al_load_bitmap(filename);
    
    sprintf(filename, "1-%d thmb.png", in_code);
    thmb = al_load_bitmap(filename);
    
    x = in_x;
    y = in_y;
    code = in_code;
}

Card::~Card(void)
{
    al_destroy_bitmap(text);
    al_destroy_bitmap(pic);
    al_destroy_bitmap(thmb);
}

void Card::DrawCard(void)
{
    al_draw_filled_rounded_rectangle(x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
    al_draw_bitmap(thmb, x + BLOCK_WIDTH / 2 - al_get_bitmap_width(thmb) / 2, y + BLOCK_HEIGHT / 2 - al_get_bitmap_height(thmb), 0);
    
    if (isHovered && !isClicked) {
        al_draw_filled_rounded_rectangle(EXP_BLOCK_X, EXP_BLOCK_Y, EXP_BLOCK_WIDTH, EXP_BLOCK_HEIGHT, EXP_BLOCK_RADIUS, EXP_BLOCK_RADIUS, WHITE);
        al_draw_bitmap(pic, EXP_BLOCK_X + EXP_BLOCK_WIDTH / 2 - al_get_bitmap_width(pic) / 2, EXP_BLOCK_Y + EXP_BLOCK_HEIGHT / 2 - al_get_bitmap_height(pic) / 2, 0);
        al_draw_bitmap(text, EXP_BLOCK_X + EXP_BLOCK_WIDTH / 2 - al_get_bitmap_width(text) / 2, EXP_BLOCK_Y + EXP_BLOCK_HEIGHT - al_get_bitmap_height(text) - 15, 0);
    }
}

void Card::UpdateXY(float new_x, float new_y)
{
    x = new_x;
    y = new_y;
}
