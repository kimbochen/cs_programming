//
//  GameWindow.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/7/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "GameWindow.hpp"

int frames = 1;

GameWindow::GameWindow()
{
    if (!al_init()) show_err_msg(-1);
    
    printf("Game Initializing...\n");
    
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    event_queue = al_create_event_queue();
    
    timer = al_create_timer(1.0 / FPS);
    cntdown = al_create_timer(1.0);
    
    if (timer == NULL || cntdown == nullptr) show_err_msg(-1);
    
    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);
    
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    
    font = al_load_ttf_font("Dancing.otf",12,0); // load small font
    Large_font = al_load_ttf_font("Dancing.otf",100,0); //load large font
    timer_font = al_load_font("timer_font.ttf", 200, 0);
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(cntdown));
    
    lv = new Level(1, 8);
//    ptimer = new Timer();
//    pviewer = new Viewer();
//    pMbutton = new MergerButton();
//    pSbutton = new ShelfButton();
//    pMdock = new MergerDock();
//    pSdock = new ShelfDock();
//    pmerger = new Merger();
//    pshelf = new Shelf();
    
    game_init();
}

void
GameWindow::game_init()
{
    icon = al_load_bitmap("icon.jpg");
    background = al_load_bitmap("background.jpg");
    mbutton = al_load_bitmap("merge_button.png");
    sbutton = al_load_bitmap("button.png");
    winBackground = al_load_bitmap("1-15 pic.png");
    loseBackground = al_load_bitmap("real_end.jpg");
    prologueBackground  = al_load_bitmap("prologue.png");
    victoryBackground = al_load_bitmap("victory.png");
    
    al_set_display_icon(display, icon);
    al_reserve_samples(3);
    
    sample = al_load_sample("ThemeSong.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_gain(backgroundSound, 0.5);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    
    sample = al_load_sample("fail_sound.wav");
    failSound = al_create_sample_instance(sample);
    al_set_sample_instance_gain(failSound, 1.0);
    al_set_sample_instance_playmode(failSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(failSound, al_get_default_mixer());
    
    sample = al_load_sample("gun_shot_sound.ogg");
    if (sample == nullptr) throw "";
    gunShotSound = al_create_sample_instance(sample);
    al_set_sample_instance_gain(gunShotSound, 1.0);
    al_set_sample_instance_playmode(gunShotSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(gunShotSound, al_get_default_mixer());
    
    lv -> InitBlocks();
//    pshelf -> InitCards();
}

void
GameWindow::game_begin()
{
    draw_running_map();
    
    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
}

void
GameWindow::game_play()
{
    int msg;
    
    srand((unsigned int)time(NULL));
    
    msg = -1;
    game_reset();
    game_begin();
    
    while(msg != GAME_EXIT) {
        msg = game_run();
        std::cout << frames << std::endl;
    }
    
    show_err_msg(msg);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;
    
    if (!al_is_event_queue_empty(event_queue))
        error = process_event();
    
    return error;
}

int
GameWindow::game_update()
{
//    Card *c1 = nullptr, *c2 = nullptr;
//
//    if (pshelf -> getCardHovered()) {
//        pviewer -> setHide(false);
//        pMdock -> setHide(true);
//
//        pviewer -> displayCard();
//    }
//
//    if (pshelf -> getCardClicked()) {
//
//        if ((pshelf -> getClickCard()).getOnMergerDock()) {
//            int space = pMdock -> getSpace();
//
//            pMdock -> setSpace(space - 1);
//            pMdock -> SetOnDock(pshelf -> getClickCard(), false);
//            pSdock -> SetOnDock(pshelf -> getClickCard(), true);
//        }
//        else if ((pshelf -> getClickCard()).getOnShelfDock()) {
//            pviewer -> setHide(true);
//            pMdock -> setHide(false);
//
//            if (pMdock -> getSpace() < 2) {
//                pMdock -> SetDestin(pshelf -> getClickCard());
//                pMdock -> SetOnDock(pshelf -> getClickCard(), true);
//                pSdock -> SetOnDock(pshelf -> getClickCard(), false);
//            }
//        }
//        else {
//            puts("shelf: checkClick malfunction");
//            return GAME_EXIT;
//        }
//    }
//
//    bool MBHide, SBHide;
//    MBHide = (pMdock -> getSpace() < 2);
//    SBHide = (pshelf -> getCardNum() <= 4);
//
//    pMbutton -> setHide(MBHide);
//    pSbutton -> setHide(SBHide);
//
//    if (pMbutton -> getClick()) {
//        pshelf -> getMergerCard(c1, c2);
//        pmerger -> MergeCards(*c1, *c2);
//
//        if (pmerger -> getIsMerged()) {
//            pshelf -> AddCard(pmerger -> getCode());
//            pSdock -> SetOnDock(pshelf -> getNewCard(pmerger -> getCode()), true);
//            pMdock -> SetOnDock(*c1, false);
//            pMdock -> SetOnDock(*c2, false);
//            pSdock -> SetOnDock(*c1, false);
//            pSdock -> SetOnDock(*c2, false);
//        }
//        else {
////            pmerger -> ReturnCards(*c1, *c2);
//            pMdock -> SetOnDock(*c1, false);
//            pMdock -> SetOnDock(*c2, false);
//            pSdock -> SetOnDock(*c1, true);
//            pSdock -> SetOnDock(*c2, true);
//        }
//    }
//
//    if (pSbutton -> getClick()) pSdock -> ToggleCardSet();
//
//    if (ptimer -> getTimerEnd()) WindowState = FAIL;
//
//    if (pshelf -> findAnsCard()) WindowState = VICTORY;
//
    if (lv -> getIsEnd()) {
        WindowState = VICTORY;
    }
    if (timebomb.getTimerEnd()) {
        WindowState = FAIL;
    }
    
    return GAME_CONTINUE;
}

int
GameWindow::process_event()
{
    int instruction = GAME_CONTINUE;
    static bool played = false;
    
    al_wait_for_event(event_queue, &event);
    
    if(redraw) {
        instruction = game_update();
        draw_running_map();
        redraw = false;
    }
    
    switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            return GAME_EXIT;
            break;
        case ALLEGRO_EVENT_TIMER:
                redraw = true;
                frames = (frames + 1) % 60;
            
//            else ptimer -> Countdown();
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
//            std::cout << mouse_x << ' ' << mouse_y << std::endl;
//            pshelf -> checkHover(mouse_x, mouse_y);
            break;
    }
    
    switch (WindowState) {
        case START:
//            puts("START");
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    al_start_timer(cntdown);
                    WindowState = PROLOGUE;
                    redraw = true;
                }
            }
            break;
        case PROLOGUE:
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    al_start_timer(cntdown);
                    WindowState = GAME;
                    redraw = true;
                }
            }
            break;
        case GAME:
//            puts("GAME");
            if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_P) {
                    WindowState = PAUSE;
                    redraw = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_M) {
                    mute = !mute;
                    if(mute)
                        al_stop_sample_instance(backgroundSound);
                    else
                        al_play_sample_instance(backgroundSound);
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (lv -> checkCompare()) {
                        if (lv -> CompareBlocks()) {
                            timebomb.Reset();
                        }
                        else {
                            timebomb.Penalty();
                            al_play_sample_instance(failSound);
                        }
                    }
                    else al_play_sample_instance(failSound);
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    lv -> ContractBlock();
                }
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                lv -> MouseHover(mouse_x, mouse_y);
//                pshelf -> checkClick(mouse_x, mouse_y);
//                pMbutton -> checkClick(mouse_x, mouse_y);
//                pSbutton -> checkClick(mouse_x, mouse_y);
            }
            else if (event.type == ALLEGRO_EVENT_TIMER) {
                if (event.timer.source == cntdown) {
                    timebomb.Countdown();
                }
            }
//            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
//                pshelf -> checkClick(mouse_x, mouse_y);
//                pMbutton -> checkClick(mouse_x, mouse_y);
//                pSbutton -> checkClick(mouse_x, mouse_y);
//            }
            break;
        case VICTORY:
            if (event.type == ALLEGRO_EVENT_TIMER) {
                if (event.timer.source == cntdown) {
                    realbomb.Countdown();
                }
            }
            if (realbomb.getTimerEnd() && !played) {
                al_play_sample_instance(gunShotSound);
                played = true;
            }
            if (played && !al_get_sample_instance_playing(gunShotSound)) {
                instruction = GAME_EXIT;
            }
            break;
        case FAIL:
            al_stop_sample_instance(backgroundSound);
            al_rest(2.0);
            instruction = GAME_EXIT;
            break;
        case PAUSE:
//            puts("PAUSE");
            al_stop_sample_instance(backgroundSound);
            al_clear_to_color(BLACK);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
                event.keyboard.keycode == ALLEGRO_KEY_P) {
                WindowState = GAME;
                al_play_sample_instance(backgroundSound);
            }
            break;
    }
    
    
    return instruction;
}

void
GameWindow::draw_running_map()
{
    al_draw_bitmap(background, 0, 0, 0);
    
    switch (WindowState) {
        case START:
            al_draw_text(Large_font, RED, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6, ALLEGRO_ALIGN_CENTER, "SHERLOCK: THE GREAT GAME");
            al_draw_text(Large_font, RED, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/4, ALLEGRO_ALIGN_CENTER, "PRESS ENTER TO START");
            al_draw_bitmap(icon, WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 - 300, ALLEGRO_ALIGN_CENTER);
            break;
        case PROLOGUE:
            al_clear_to_color(WHITE);
            al_draw_bitmap(prologueBackground, (WINDOW_WIDTH - al_get_bitmap_width(prologueBackground)) / 2, (WINDOW_HEIGHT - al_get_bitmap_height(prologueBackground)) / 2, 0);
            al_draw_text(Large_font, BLACK, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 150.0, ALLEGRO_ALIGN_CENTER, "PRESS ENTER TO CONTINUE");
            break;
        case GAME:
            if (lv -> getcanCompare()) {
                lv -> DrawCompare();
            }
            else {
                lv -> DrawBlocks();
                timebomb.Draw(timer_font);
            }
            
//            ptimer -> Draw(timer_font);
            
//            al_draw_filled_rounded_rectangle(SHELF_W, VIEWER_H / 2, WINDOW_WIDTH, VIEWER_H, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
//            al_draw_bitmap(mbutton, (SHELF_W + WINDOW_WIDTH - al_get_bitmap_width(mbutton)) / 2, VIEWER_H * 3/4 - al_get_bitmap_height(mbutton) / 2, 0);
//
//            al_draw_filled_rounded_rectangle(SHELF_W, VIEWER_H, WINDOW_WIDTH, WINDOW_HEIGHT, BLOCK_RADIUS, BLOCK_RADIUS, WHITE);
//            al_draw_bitmap(sbutton, (SHELF_W + WINDOW_WIDTH - al_get_bitmap_width(sbutton)) / 2, VIEWER_H + SHELF_H / 2 - al_get_bitmap_height(sbutton), 0);
            
//            pMdock -> Draw();
//
//            pSdock -> Draw(min(pshelf -> getCardNum(), 4));
//
//            pshelf -> Draw(pSdock -> getCardSet());
            
            break;
        case VICTORY:
            al_clear_to_color(WHITE);
            al_stop_sample_instance(backgroundSound);
            al_draw_bitmap(winBackground, 0.0, WINDOW_HEIGHT - al_get_bitmap_height(winBackground), 0);
            al_draw_bitmap(victoryBackground, (WINDOW_WIDTH - al_get_bitmap_width(victoryBackground)), WINDOW_HEIGHT / 4, 0);
            al_draw_text(Large_font, BLACK, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/4, ALLEGRO_ALIGN_CENTER, "YOU WIN");
            if (realbomb.getTimerEnd()) {
                al_clear_to_color(BLACK);
                al_draw_bitmap(loseBackground, (WINDOW_WIDTH - al_get_bitmap_width(loseBackground)) / 2, (WINDOW_HEIGHT - al_get_bitmap_height(loseBackground)) / 2, 0);
                al_draw_text(Large_font, WHITE, WINDOW_WIDTH / 2, 10.0, ALLEGRO_ALIGN_CENTER, "SORRY BOYS, I AM SOOO CHNGEABLE!");
            }
            break;
        case FAIL:
            al_clear_to_color(RED);
            al_draw_bitmap(loseBackground, (WINDOW_WIDTH - al_get_bitmap_width(loseBackground)) / 2, (WINDOW_HEIGHT - al_get_bitmap_height(loseBackground)) / 2, 0);
            break;
        case PAUSE:
            al_clear_to_color(WHITE);
            al_draw_text(Large_font, WHITE, WINDOW_WIDTH, WINDOW_HEIGHT, ALLEGRO_ALIGN_CENTER, "PAUSED");
            break;
    }
    
    
    al_flip_display();
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);
    
    game_destroy();
    exit(9);
}

void
GameWindow::game_reset()
{
    mute = false;
    redraw = false;
    
    al_stop_sample_instance(backgroundSound);
    
    al_stop_timer(timer);
}

void
GameWindow::game_destroy()
{
    game_reset();
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    al_destroy_font(font);
    al_destroy_font(Large_font);
    al_destroy_font(timer_font);
    
    al_destroy_timer(timer);
    al_destroy_timer(cntdown);
    
    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    al_destroy_bitmap(mbutton);
    al_destroy_bitmap(sbutton);
    al_destroy_bitmap(winBackground);
    al_destroy_bitmap(loseBackground);
    al_destroy_bitmap(prologueBackground);
    al_destroy_bitmap(victoryBackground);
    
    al_destroy_sample(sample);
    al_destroy_sample_instance(backgroundSound);
    al_destroy_sample_instance(failSound);
    al_destroy_sample_instance(gunShotSound);
    
    delete lv;
    
//    delete ptimer;
//    delete pviewer;
//    delete pMbutton;
//    delete pSbutton;
//    delete pMdock;
//    delete pSdock;
//    delete pmerger;
//    delete pshelf;
}
