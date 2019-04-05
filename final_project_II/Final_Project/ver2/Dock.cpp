//
//  Dock.cpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#include "Dock.hpp"

Dock::Dock(void)
{
    float start_x = 15.0, start_y = EXP_BLOCK_Y + 30.0;
    
    for (int i = 1; i <= 7; i ++) {
        Card *c = new Card(start_x, start_y, i);
        CardSet.push_back(c);
        start_x += BLOCK_WIDTH + 15.0;
        if (i == 4) start_x = 15.0;
    }
    
    button = al_load_bitmap("button.png");
    
    button_x = WINDOW_WIDTH - al_get_bitmap_width(button);
    button_y = (EXP_BLOCK_Y + WINDOW_HEIGHT) / 2 + 7.5;
}

void Dock::DrawDock(void)
{
    al_draw_filled_rectangle(0.0, EXP_BLOCK_Y + 15.0, WINDOW_WIDTH, WINDOW_HEIGHT, GRAY);
    
    if (!isRotate) start = 4;
    
    for (int i = start; i <= start + 4 && i < CardSet.size(); i ++) {
        CardSet[i] -> DrawCard();
    }
    
    al_draw_bitmap(button, button_x, button_y, 0);
}

void Dock::MouseHover(float ms_x, float ms_y)
{
    for (int i = start; i < start + 4 && i < CardSet.size(); i ++) {
        Card *c = CardSet[i];
        if (c -> getX() <= ms_x && ms_x <= c -> getX() + BLOCK_WIDTH &&
            c -> getY() <= ms_y && ms_y <= c -> getY() + BLOCK_HEIGHT) {
            c -> ToggleHover();
        }
    }
}

void Dock::MouseClick(float ms_x, float ms_y)
{
    for (int i = start; i < start + 4 && i < CardSet.size(); i ++) {
        Card *c = CardSet[i];
        if (c -> getX() <= ms_x && ms_x <= c -> getX() + BLOCK_WIDTH &&
            c -> getY() <= ms_y && ms_y <= c -> getY() + BLOCK_HEIGHT) {
            c -> UpdateXY(ms_x, ms_y);
        }
    }
    
    if (button_x <= ms_x && ms_x <= button_x + BLOCK_WIDTH &&
        button_y <= ms_y && ms_y <= button_y + BLOCK_HEIGHT) {
        isRotate = !isRotate;
    }
}

void Dock::AddCard(Card *in)
{
    CardSet.push_back(in);
}
