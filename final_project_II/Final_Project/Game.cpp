//
//  Game.cpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/21/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#include "Game.hpp"

Game::Game(void)
{
    if (!al_init()) throw "init fail";
    
    display = al_create_display(WIN_W, WIN_H);
    event_queue = al_create_event_queue();
    if (display == NULL || event_queue == NULL)
        throw "init fail";
    
    timer = al_create_timer(1.0 / FPS);
    cntdown = al_create_timer(1.0);
    if (timer == NULL || cntdown == nullptr)
        throw "init fail";
    
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    
    font = al_load_ttf_font("Dancing.otf",12,0);
    Large_font = al_load_ttf_font("Dancing.otf",100,0);
    timer_font = al_load_font("timer_font.ttf", 200, 0);
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(cntdown));
    
    testCard.setPos(SHELF_X(0), SHELF_Y);
    
    game_init();
}

Game::~Game(void)
{
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
    al_destroy_bitmap(sign);
    al_destroy_bitmap(text);
    al_destroy_bitmap(pic);
    al_destroy_bitmap(thumbnail);
    
    al_destroy_sample(sample);
    al_destroy_sample_instance(backgroundSound);
}

void
Game::game_init()
{
    icon = al_load_bitmap("icon.jpg");
    background = al_load_bitmap("background.jpg");
    mbutton = al_load_bitmap("merge_button.png");
    sbutton = al_load_bitmap("button.png");
    sign = al_load_bitmap("sign.jpg");
    
    al_set_display_icon(display, icon);
    al_reserve_samples(2);
    
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
}

void
Game::game_play()
{
    draw_running_map();
    
    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
    
    int msg = -1;
    
    while(msg != GAME_EXIT) {
        msg = game_run();
    }
}

int
Game::game_run()
{
    int error = GAME_CONTINUE;
    
    if (!al_is_event_queue_empty(event_queue))
        error = process_event();
    
    return error;
}

int
Game::game_update()
{
    if (testCard.getClick()) {
        std::cout << testDock.getSpace();
        testCard.moveTo(DOCK);
        testCard.setPos(DOCK_X(testDock.getSpace()), DOCK_Y);
        testDock.occupy();
    }
    
    if (testTimer.getTimerEnd()) {
        window = FAIL;
    }
    
    return GAME_CONTINUE;
}

int
Game::process_event()
{
    int instruction = GAME_CONTINUE;
    
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
            if (event.timer.source == timer) redraw = true;
            else testTimer.Countdown();
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
//            std::cout << mouse_x << ' ' << mouse_y << std::endl;
            testCard.checkHover(mouse_x, mouse_y);
            break;
    }
    
    switch (window) {
        case START:
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    al_start_timer(cntdown);
                    window = PROLOGUE;
                    redraw = true;
                }
            }
            break;
        case PROLOGUE:
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    al_start_timer(cntdown);
                    window = STAGE;
                    redraw = true;
                }
            }
            break;
        case STAGE:
            if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_P) {
                    window = PAUSE;
                    redraw = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_M) {
                    mute = !mute;
                    if(mute)
                        al_stop_sample_instance(backgroundSound);
                    else
                        al_play_sample_instance(backgroundSound);
                }
                
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                testCard.checkClick(mouse_x, mouse_y);
            }
            break;
        case VICTORY:
            break;
        case FAIL:
            break;
        case PAUSE:
            al_stop_sample_instance(backgroundSound);
            al_clear_to_color(BLACK);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN &&
                event.keyboard.keycode == ALLEGRO_KEY_P) {
                window = STAGE;
                al_play_sample_instance(backgroundSound);
            }
            break;
    }
    
    
    return instruction;
}

void
Game::draw_running_map()
{
    al_draw_bitmap(background, 0, 0, 0);
    
    switch (window) {
        case START:
            al_draw_text(Large_font, RED, WIN_W / 2, WIN_H / 6, ALLEGRO_ALIGN_CENTER, "SHERLOCK: THE GREAT GAME");
            al_draw_text(Large_font, RED, WIN_W / 2, WIN_H * 3/4, ALLEGRO_ALIGN_CENTER, "PRESS ENTER TO START");
            al_draw_bitmap(icon, WIN_W / 2 - 300, WIN_H / 2 - 300, ALLEGRO_ALIGN_CENTER);
            break;
        case PROLOGUE:
            al_clear_to_color(BLACK);
            break;
        case STAGE:
            for (int i = 0; i < 4; i ++) {
                al_draw_filled_rounded_rectangle(SHELF_X(i), SHELF_Y, SHELF_X(i) + CARD_W, SHELF_Y + CARD_H, CARD_R, CARD_R, WHITE);
            }
            
            sprintf(filename, "1-%d text.png", testCard.getCode());
            text = al_load_bitmap(filename);

            sprintf(filename, "1-%d pic.png", testCard.getCode());
            pic = al_load_bitmap(filename);

            sprintf(filename, "1-%d thmb.png", testCard.getCode());
            thumbnail = al_load_bitmap(filename);

            al_draw_bitmap(thumbnail, SHELF_X(0) + (CARD_W - al_get_bitmap_width(thumbnail)) / 2, SHELF_Y + 10.0, 0);
            
            if (testCard.getHover()) {
                w1 = al_get_bitmap_width(pic);
                h1 = al_get_bitmap_height(pic);
                
                w2 = al_get_bitmap_width(text);
                h2 = al_get_bitmap_height(text);
                
                al_draw_bitmap(pic, (SHELF_W - w1) / 2, (SHELF_H - h1 - h2) / 3, 0);
                al_draw_bitmap(text, (SHELF_W - w2) / 2, SHELF_H - (SHELF_H - h1 - h2) / 3, 0);
            } else {
                for (int i = 0; i < 2; i ++) {
                    al_draw_filled_rounded_rectangle(DOCK_X(i), DOCK_Y, DOCK_X(i) + CARD_W, DOCK_Y + CARD_H, CARD_R, CARD_R, WHITE);
                }
                al_draw_bitmap(sign, SHELF_W / 2 - al_get_bitmap_width(sign) / 2, (VIEWER_H - al_get_bitmap_height(sign)) / 2, 0);
            }
            
            
            tlen = testTimer.getTime();
            al_draw_filled_rounded_rectangle(SHELF_W, 10.0, WIN_W - 10.0, VIEWER_H / 2 - 10.0, CARD_R, CARD_R, WHITE);
            sprintf(timeText, "%d", tlen);
            al_draw_text(timer_font, RED, (SHELF_W + WIN_W - 10.0) / 2, 100.0, ALLEGRO_ALIGN_CENTER, timeText);
            
            al_draw_filled_rounded_rectangle(SHELF_W, VIEWER_H / 2, WIN_W - 10.0, VIEWER_H - 10.0, CARD_R, CARD_R, WHITE);
            al_draw_bitmap(mbutton, (SHELF_W + WIN_W - al_get_bitmap_width(mbutton)) / 2, VIEWER_H * 3/4 - al_get_bitmap_height(mbutton) / 2, 0);
            
            al_draw_filled_rounded_rectangle(SHELF_W, VIEWER_H, WIN_W - 10.0, WIN_H - 10.0, CARD_R, CARD_R, WHITE);
            al_draw_bitmap(sbutton, (SHELF_W + WIN_W - al_get_bitmap_width(sbutton)) / 2, VIEWER_H + (SHELF_H - al_get_bitmap_height(sbutton)) / 2, 0);
            
            break;
        case VICTORY:
            al_clear_to_color(WHITE);
            break;
        case FAIL:
            al_clear_to_color(RED);
            break;
        case PAUSE:
            al_draw_text(Large_font, WHITE, WIN_W, WIN_H, ALLEGRO_ALIGN_CENTER, "PAUSED");
            break;
    }
    
    
    al_flip_display();
}


