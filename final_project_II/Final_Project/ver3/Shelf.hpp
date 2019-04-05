//
//  Shelf.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Shelf_hpp
#define Shelf_hpp

#include "global.hpp"
#include "Card.hpp"

class Shelf {
    std::vector<Card> CardSet;
    Card hoverC;
    bool CardClicked = false;
    bool CardHovered = false;
    bool end = false;
    int CardNum = 15;
    int count;
    float d = SHELF_W / 4 - BLOCK_WIDTH;
    float x = d / 2;
    float y = (SHELF_H - BLOCK_HEIGHT) / 2;
    
public:
    Shelf(void) {}
    ~Shelf(void) {}
    
    void InitCards(void);
    void Draw(bool);
    
    void checkClick(float, float);
    
    bool getCardClicked(void) { return CardClicked; }
    void AddCard(int c) { CardSet.push_back(*(new Card(c))); }
    Card& getClickCard(void) { return hoverC; }
    
    void getMergerCard(Card *, Card *);
    Card& getNewCard(int);
    
    void checkHover(float, float);
    Card& getHoverCard(void) { return hoverC; }
    bool getCardHovered(void) { return CardHovered; }
    
    int getCardNum(void) { return CardNum; }
    bool findAnsCard(void) { return end; }
};

#endif /* Shelf_hpp */
