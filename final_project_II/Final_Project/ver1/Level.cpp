//
//  Level.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/13/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Level.hpp"

Level::Level(int in_levelnum, int in_blocknum)
{
    level_num = in_levelnum;
    block_num = in_blocknum;
    
    for (int i = 0; i < 8; i ++) {
        char filename[20];
        sprintf(filename, "spark-%d.png", i);
        spark[i] = al_load_bitmap(filename);
    }
}

Level::~Level(void)
{
    for (ALLEGRO_BITMAP *sp : spark) {
        al_destroy_bitmap(sp);
    }
    al_destroy_font(Large_font);
    al_destroy_font(timer_font);
    BlockSet.clear();
    BlockCode.clear();
}

bool Level:: checkCompare(void)
{
    int click_num = 0;
    
    for (auto bp : BlockSet) {
        if (bp->getSelected()) {
            click_num ++;
        }
    }
    std::cout << click_num << std::endl;
    
    canCompare = (click_num == 2);
    
    return canCompare;
}

void Level::DrawBlocks(void)
{
    float x = 0.0, y = 10.0;
    
    for (auto bp : BlockSet) {
        if (bp -> getExpanded()) {
            bp -> Draw(x, y);
            return;
        }
    }
    
    for (auto b : BlockSet) {
        b -> Draw(x, y);
        x += BLOCK_WIDTH + 15.0;
        if (x + 15.0 >= WINDOW_WIDTH) {
            x = 15.0;
            y += BLOCK_HEIGHT + 30.0;
        }
    }
    
    canCompare = false;
    
    return;
}

void Level::DrawWrongAns(void)
{
    al_clear_to_color(RED);
    al_draw_text(Large_font, BLACK, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3, ALLEGRO_ALIGN_CENTER, "WRONG COMBINATION, TIME PENALTY!!!");
}

void Level::DrawCompare(void)
{
    static int i = 0;
    if (i == 60) {
        i = 0;
        canCompare = false;
    }
    else {
        if (cmpResults) {
            al_clear_to_color(BLACK);
            bp1 -> Draw(10.0, (WINDOW_HEIGHT - BLOCK_HEIGHT) / 2);
            bp2 -> Draw(WINDOW_WIDTH - BLOCK_WIDTH - 10.0, (WINDOW_HEIGHT - BLOCK_HEIGHT) / 2);
            al_draw_bitmap(spark[i % 8], (WINDOW_WIDTH - al_get_bitmap_width(spark[frames % 8])) / 2, (WINDOW_HEIGHT - al_get_bitmap_height(spark[i % 8])) / 2, 0);
        }
        else DrawWrongAns();
    }
    i ++;
}

void Level::InitBlocks(void)
{
    for (int i = 1; i <= block_num; i ++) {
//        puts("new block");
        Block *bp = new Block(WHITE, 1, i);
        BlockSet.push_back(bp);
    }
    
    if (level_num == 1) {
        BlockCode[std::make_pair(1, 2)] = 9;
        BlockCode[std::make_pair(3, 4)] = 10;
        BlockCode[std::make_pair(5, 10)] = 11;
        BlockCode[std::make_pair(6, 11)] = 12;
        BlockCode[std::make_pair(9, 12)] = 13;
        BlockCode[std::make_pair(7, 13)] = 14;
        BlockCode[std::make_pair(8, 14)] = 15;
    }
    else if (level_num == 2) {
        BlockCode[std::make_pair(1, 2)] = 8;
        BlockCode[std::make_pair(3, 4)] = 9;
        BlockCode[std::make_pair(5, 9)] = 10;
        BlockCode[std::make_pair(8, 10)] = 11;
        BlockCode[std::make_pair(6, 11)] = 12;
        BlockCode[std::make_pair(7, 12)] = 13;
    }
}

bool Level::CompareBlocks(void)
{
    cmpResults = true;
    std::list<Block *>::iterator it1, it2;
    
    it1 = std::find_if(std::begin(BlockSet), std::end(BlockSet),
                      [&](Block *b) { return b->getSelected(); });
    it2 = std::find_if(std::begin(BlockSet), std::end(BlockSet),
                      [&](Block *b) { return b->getSelected() && b != *it1; });
    
    bp1 = *it1;
    bp2 = *it2;
    
    auto rel = std::make_pair((*it1)->getCode(), (*it2)->getCode());
    
    if (BlockCode.find(rel) != BlockCode.end()) {
        Block *bp = new Block(GRAY, level_num, BlockCode[rel]);
        BlockSet.push_back(bp);
        BlockSet.erase(it1);
        BlockSet.erase(it2);
    }
    else cmpResults = false;
    
    return cmpResults;
}

void Level::MouseHover(int mouse_x, int mouse_y)
{
    for (auto bp : BlockSet) {
        if (bp -> getExpanded()) return;
    }
    
    for (auto bp : BlockSet) {
        if (bp->getX() <= mouse_x && mouse_x <= bp->getX() + BLOCK_WIDTH &&
            bp->getY() <= mouse_y && mouse_y <= bp->getY() + BLOCK_HEIGHT) {
//            bp->ToggleClick();
            if (bp -> getSelected() == false) bp -> ToggleExpand();
            bp -> ToggleSelect();
        }
    }
}

void Level::ExpandBlock(void)
{
    for (auto bp : BlockSet) {
        if (bp -> getClicked()) {
            bp -> ToggleExpand();
            break;
        }
    }
}

void Level::ContractBlock(void)
{
    for (auto bp : BlockSet) {
        if (bp -> getExpanded()) {
            if (bp -> getCode() == 15)
                isEnd = true;
            else
                bp -> ToggleExpand();
        }
    }
}
