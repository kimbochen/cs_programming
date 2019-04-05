//
//  Game.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/21/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Main.hpp"
#include "Card.hpp"
#include "Timer.hpp"
#include "Dock.hpp"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

typedef enum { START, PROLOGUE, STAGE, VICTORY, FAIL, PAUSE } STATE;

class Game {
public:
    Game(void);
    ~Game(void);
    
    void game_init();
    void game_play();
    int game_run();
    
    int game_update();
    int process_event();
    void draw_running_map();
    
private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *mbutton = nullptr;
    ALLEGRO_BITMAP *sbutton = nullptr;
    ALLEGRO_BITMAP *sign = nullptr;
    ALLEGRO_BITMAP *text = nullptr;
    ALLEGRO_BITMAP *pic = nullptr;
    ALLEGRO_BITMAP *thumbnail = nullptr;
    
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
    
    STATE window = START;
    int mouse_x, mouse_y;
    bool redraw = false;
    bool mute = false;
    char timeText[3];
    int tlen;
    std::vector<Card> CardSet;
    Timer testTimer;
    Card testCard{1};
    Dock testDock;
    char filename[20];
    float w1, h1, w2, h2;
};

#endif /* Game_hpp */
