//
//  Level.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/13/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include "global.hpp"
#include "Block.hpp"

class Level {
private:
    int level_num;
    int block_num;
    bool isEnd = false;
    bool canCompare = false;
    bool cmpResults;
    Block *bp1 = nullptr, *bp2 = nullptr;
    std::list<Block *> BlockSet;
    std::map<std::pair<int, int>, int> BlockCode;
    ALLEGRO_BITMAP *spark[8];
    ALLEGRO_FONT *Large_font = al_load_ttf_font("Dancing.otf",100,0);
    ALLEGRO_FONT *timer_font = al_load_font("timer_font.ttf", 200, 0);
public:
    Level(int, int);
    ~Level(void);
    bool checkCompare(void);
    void DrawBlocks(void);
    void DrawCompare(void);
    void DrawWrongAns(void);
    void InitBlocks(void);
    void MouseHover(int, int);
    void ExpandBlock(void);
    void ContractBlock(void);
    bool getIsEnd(void) { return isEnd; }
    bool getcanCompare(void) { return canCompare; }
    bool CompareBlocks(void);
    bool getCmpResults(void) { return cmpResults; }
};

#endif /* Level_hpp */
