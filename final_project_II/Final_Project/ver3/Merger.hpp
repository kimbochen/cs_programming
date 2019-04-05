//
//  Merger.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/20/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Merger_hpp
#define Merger_hpp

#include "global.hpp"
#include "Card.hpp"

class Merger {
    std::map<std::pair<int, int>, int> CardCode;
    bool isMerged;
    int Code;
public:
    Merger(void);
    ~Merger(void) { CardCode.clear(); }
    
    void MergeCards(Card &, Card &);
    int getCode(void) { return Code; }
    bool getIsMerged(void) { return isMerged; }
    void ReturnCards(Card &, Card &);
};

#endif /* Merger_hpp */
