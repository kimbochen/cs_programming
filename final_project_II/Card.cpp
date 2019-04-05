//
//  Card.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/21/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Card.hpp"

Card::Card(int in_code)
{
    code = in_code;
}

Card::~Card(void)
{
}

void Card::checkClick(float ms_x, float ms_y)
{
    checkHover(ms_x, ms_y);
    click = hover;
    std::cout << click << std::endl;
}

void Card::setPos(float in_x, float in_y)
{
    x = in_x;
    y = in_y;
}

void Card::checkHover(float ms_x, float ms_y)
{
    hover = (x <= ms_x && ms_x <= x + CARD_W &&
             y <= ms_y && ms_y <= y + CARD_H);
}
