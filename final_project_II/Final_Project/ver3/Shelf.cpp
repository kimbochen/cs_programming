//
//  Shelf.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Shelf.hpp"

void Shelf::InitCards(void)
{
    for (int i = 1; i <= 8; i ++) {
        Card *c = new Card(i);
        CardSet.push_back(*c);
    }
}

void Shelf::Draw(bool isFormer)
{
    if (isFormer) count = 4;
    else count = 0;
    
    for (int i = 0, j = 0; i < 4 && i < CardSet.size(); i ++) {
        if (CardSet[i].getOnShelfDock()) {
            if (count == 0) {
                CardSet[i].setPos(x + j * d, y);
                CardSet[i].Draw();
                j ++;
            }
            count --;
        }
    }
}

Card& Shelf::getNewCard(int targ)
{
    for (Card c : CardSet) {
        if (c.getCode() == targ) return c;
    }
}

void Shelf::checkClick(float ms_x, float ms_y)
{
    checkHover(ms_x, ms_y);
    CardClicked = CardHovered;
}

void Shelf::getMergerCard(Card *c1, Card *c2)
{
    for (Card c : CardSet) {
        if (c.getOnMergerDock()) {
            if (c1) c1 = &c;
            else c2 = &c;
        }
    }
}

void Shelf::checkHover(float ms_x, float ms_y)
{
    bool ishover;
    for (Card c : CardSet) {
        ishover = (c.getX() <= ms_x && ms_x <= c.getX() + BLOCK_WIDTH &&
                   c.getY() <= ms_y && ms_y <= c.getY() + BLOCK_HEIGHT);
        if (c.getOnShelfDock()) {
            c.setHover(ishover);
            hoverC = c;
            CardHovered = true;
            return;
        }
    }
    
    CardHovered = false;
}


