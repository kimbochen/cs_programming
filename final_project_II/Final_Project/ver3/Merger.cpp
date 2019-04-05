//
//  Merger.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Merger.hpp"

Merger::Merger(void)
{
    CardCode[std::make_pair(1, 2)] = 9;
    CardCode[std::make_pair(3, 4)] = 10;
    CardCode[std::make_pair(5, 10)] = 11;
    CardCode[std::make_pair(6, 11)] = 12;
    CardCode[std::make_pair(9, 12)] = 13;
    CardCode[std::make_pair(7, 13)] = 14;
    CardCode[std::make_pair(8, 14)] = 15;
}

void Merger::MergeCards(Card &c1, Card &c2)
{
    auto rel = std::make_pair(min(c1.getCode(), c2.getCode()), max(c1.getCode(), c2.getCode()));
    
    isMerged = (CardCode.find(rel) != CardCode.end());
    
    if (isMerged) {
        Code = CardCode[rel];
    }
    
}

void Merger::ReturnCards(Card &c1, Card &c2)
{
    c1.setOnMergerDock(false);
    c1.setOnShelfDock(true);
    
    c2.setOnMergerDock(false);
    c2.setOnShelfDock(true);
}
