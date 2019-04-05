//
//  Timer.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Timer.hpp"

void Timer::Draw(ALLEGRO_FONT *font)
{
    al_draw_filled_rounded_rectangle(x, y, x + MENU_W / 2, y + VIEWER_H * 2/5, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
    sprintf(text, "%d", tlen);
    al_draw_text(font, RED, x + 10.0, y + 10.0, ALLEGRO_ALIGN_LEFT, text);
}

void Timer::Countdown(void)
{
    tlen --;
    if (tlen <= 0) timerEnd = true;
}
