//
//  GameWindow.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/7/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef GameWindow_hpp
#define GameWindow_hpp

#include "global.hpp"
#include "Level.hpp"
#include "Block.hpp"
#include "Timer.hpp"
//#include "Viewer.hpp"
//#include "MergerButton.hpp"
//#include "ShelfButton.hpp"
//#include "MergerDock.hpp"
//#include "ShelfDock.hpp"
//#include "Merger.hpp"
//#include "Shelf.hpp"
//#include "Card.hpp"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

class GameWindow
{
public:
    GameWindow();
    
    void game_init();
    void game_begin();
    void game_play();
    int game_run();
    
    int game_update();
    int process_event();
    void draw_running_map();
    
    void show_err_msg(int msg);
    void game_reset();
    void game_destroy();
    
private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *mbutton = nullptr;
    ALLEGRO_BITMAP *sbutton = nullptr;
    ALLEGRO_BITMAP *winBackground = nullptr;
    ALLEGRO_BITMAP *prologueBackground = nullptr;
    ALLEGRO_BITMAP *victoryBackground = nullptr;
    ALLEGRO_BITMAP *loseBackground = nullptr;
    ALLEGRO_DISPLAY* display = NULL;
    
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *timer_font = nullptr;
    
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *cntdown = nullptr;
    
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *gunShotSound = nullptr;
    
    int WindowState = START;
    int mouse_x, mouse_y;
    bool redraw = false;
    bool mute = false;
    Level *lv = nullptr;
    Timer timebomb {60};
    Timer realbomb {3};
    bool suprise = false;
//    Timer *ptimer = nullptr;
//    Viewer *pviewer = nullptr;
//    MergerButton *pMbutton = nullptr;
//    ShelfButton *pSbutton = nullptr;
//    MergerDock *pMdock = nullptr;
//    ShelfDock *pSdock = nullptr;
//    Merger *pmerger = nullptr;
//    Shelf *pshelf = nullptr;
};

#endif /* GameWindow_hpp */
