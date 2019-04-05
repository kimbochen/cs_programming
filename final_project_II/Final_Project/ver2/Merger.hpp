//
//  Merger.hpp
//  
//
//  Created by Kimbo Chen on 6/19/18.
//

#ifndef Merger_hpp
#define Merger_hpp

#include "global.hpp"
#include "Card.hpp"

class Merger {
    Card *lf = nullptr;
    Card *rt = nullptr;
    ALLEGRO_BITMAP *plus_sign = nullptr;
    float lf_x, lf_y;
    float rt_x, rt_y;
    float sign_x, sign_y;
    bool canMerge = false;
    bool GameEnd = false;
    
public:
    Merger(void);
    ~Merger(void);
    void DrawMerger(void);
    void CardHover(void);
    void DetectCards(void);
    void MergeCards(void);
    bool getCanMerge(void) { return canMerge; }
};

#endif /* Merger_hpp */
