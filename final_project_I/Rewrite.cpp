#include "Header.hpp"

int main(int argc, char *argv[]) {
    int msg = 0;
    
    game_init();
    game_begin();
    
    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }
    
    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

void game_init(void) {
    if (!al_init()) {
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-1);
    }
    
    display = al_create_display(WIDTH / 2, HEIGHT / 2);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1 / FPS);
    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }
    
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "106062202");
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    p1.ID = PLAYER1;
    p2.ID = PLAYER2;
    InitPlayer(p1);
    InitPlayer(p2);
    
    InitBullet(bullets1, NUM_BULLETS);
    InitBullet(bullets2, NUM_BULLETS);
}

void game_begin(void) {
    song = al_load_sample( "hello.wav" );
    if (!song){
        printf( "Audio clip sample not loaded!\n" );
        show_err_msg(-1);
    }
    // Loop the song until the display closes
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    
    al_start_timer(timer);
}

int process_event(void) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    
    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (frame == START) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ENTER:
                    frame = GAME;
                    break;
                case ALLEGRO_KEY_A:
                    frame = ABOUT;
                    break;
                case ALLEGRO_KEY_E:
                    return GAME_TERMINATE;
            }
        }
        else if (frame == ABOUT) {
            if (event.keyboard.keycode == ALLEGRO_KEY_R) {
                frame = START;
            }
        }
        else if (frame == GAME) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    if (!p2.keys[JUMP]) {
                        p2.keys[JUMP] = true;
                        p2.dy = -45;
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
                    p2.keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    p2.keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    p2.keys[SHOOT] = true;
                    FireBullet(bullets2, NUM_BULLETS, p2);
                    break;
                
                case ALLEGRO_KEY_W:
                    if (!p1.keys[JUMP]) {
                        p1.keys[JUMP] = true;
                        p1.dy = -45;
                    }
                    break;
                case ALLEGRO_KEY_D:
                    p1.keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_A:
                    p1.keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_LSHIFT:
                    p1.keys[SHOOT] = true;
                    FireBullet(bullets1, NUM_BULLETS, p1);
                    break;
                
                case ALLEGRO_KEY_ESCAPE:
                    redraw = false;
                    return GAME_TERMINATE;
            }
        }
        else if (frame == MENU) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_R:
                    frame = GAME;
                    game_init();
                    game_begin();
                    break;
                case ALLEGRO_KEY_E:
                    redraw = false;
                    return GAME_TERMINATE;
            }
        }
    }
    if (event.type == ALLEGRO_EVENT_KEY_UP) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_RIGHT:
                p2.keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                p2.keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_LSHIFT:
                p2.keys[SHOOT] = false;
                break;
            
            case ALLEGRO_KEY_D:
                p1.keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_A:
                p1.keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                p1.keys[SHOOT] = false;
                break;
        }
    }
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        redraw = false;
        return GAME_TERMINATE;
    }
    
    return 0;
}

int game_run(void) {
    int error = 0;
    
    error = process_event();
    
    if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = false;
        
        if (frame == START) {
            DrawStart();
        }
        else if (frame == GAME) {
            
            background = al_load_bitmap("stage.jpg");
            al_draw_bitmap(background, 0,0, 0);
            
            DrawPlayer(p1);
            DrawBullet(bullets1, NUM_BULLETS);
            Jump(p1);
            if (p1.keys[RIGHT]) MoveRight(p1);
            if (p1.keys[LEFT]) MoveLeft(p1);
//            printf("%lf\n", p1.x);
            UpdateBullet(bullets1, NUM_BULLETS);
            CollideBullet(bullets1, NUM_BULLETS, p2);
            
            
            DrawPlayer(p2);
            DrawBullet(bullets2, NUM_BULLETS);
            Jump(p2);
            if (p2.keys[RIGHT]) MoveRight(p2);
            if (p2.keys[LEFT]) MoveLeft(p2);
//            printf("%lf\n", p2.x);
            UpdateBullet(bullets2, NUM_BULLETS);
            CollideBullet(bullets2, NUM_BULLETS, p1);
            
            if (p1.lives == 0 || p2.lives == 0) {
                frame = MENU;
            }
        }
        else if (frame == ABOUT) {
            DrawAbout();
        }
        else if (frame == MENU) {
            DrawMenu();
        }
        
        al_flip_display();
    }
    
    return error;
}

void game_destroy(void) {
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_sample(song);
    al_destroy_font(font);
    al_destroy_bitmap(background);
    al_destroy_bitmap(p1.image_path);
    al_destroy_bitmap(p1.lives_path);
    al_destroy_bitmap(p2.image_path);
    al_destroy_bitmap(p2.lives_path);
}

void CollideBullet(Bullet bullet[], int size, player &p) {
    for (int i = 0; i < size; i ++) {
        if (bullet[i].alive) {
            if (bullet[i].x > (p.x - p.bound_x) && bullet[i].x < (p.x + p.bound_x) &&
                bullet[i].y > (p.y - p.bound_y) && bullet[i].y < (p.y + p.bound_y))
            {
                bullet[i].alive = false;
                p.lives --;
            }
        }
    }
}

void DrawStart(void) {
    al_clear_to_color(al_map_rgb(100,100,100));
    font = al_load_ttf_font("pirulen.ttf",12,0);
    
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2 - 50, ALLEGRO_ALIGN_CENTER, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/2 - 120, HEIGHT/2 - 60, WIDTH/2 + 120, HEIGHT/2 - 20, al_map_rgb(255, 255, 255), 0);
    
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "Press 'A' to about");
    al_draw_rectangle(WIDTH/2 - 120, HEIGHT/2 - 10, WIDTH/2 + 120, HEIGHT/2 + 30, al_map_rgb(255, 255, 255), 0);
    
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2 + 50, ALLEGRO_ALIGN_CENTER, "Press 'E' to exit");
    al_draw_rectangle(WIDTH/2 - 120, HEIGHT/2 + 40, WIDTH/2 + 120, HEIGHT/2 + 80, al_map_rgb(255, 255, 255), 0);
}

void Jump(player &p) {
    p.y += p.dy;
    p.dy += 2.5;
    if (p.y >= HEIGHT/2 + 150) {
        p.y = HEIGHT/2 + 150;
        p.keys[JUMP] = false;
        p.dy = 0;
    }
}

void MoveRight(player &p) {
    
    if (p.ID == PLAYER1 && p.x < BOUND_R1) p.x += p.dx;
    if (p.ID == PLAYER2 && p.x < BOUND_R2) p.x += p.dx;
}

void MoveLeft(player &p) {
    if (p.ID == PLAYER1 && p.x > BOUND_L1) p.x -= p.dx;
    if (p.ID == PLAYER2 && p.x > BOUND_L2) p.x -= p.dx;
}

void DrawPlayer(player &p) {
    if (p.ID == PLAYER1) {
        p.lives_path = al_load_bitmap("heart.png");
        p.image_path = al_load_bitmap("maokai.png");
        al_draw_bitmap(p.image_path, p.x, p.y, 0);
        
        for (int i = 0; i < p1.lives; i ++) {
            al_draw_bitmap(p1.lives_path, i * 50, 0, 0);
        }
    }
    else if (p.ID == PLAYER2){
        p.lives_path = al_load_bitmap("heart.png");
        p.image_path = al_load_bitmap("teemo.png");
        al_draw_bitmap(p.image_path, p.x, p.y, 0);
        al_draw_bitmap(p.lives_path, WIDTH, 0, 0);
        
        for (int i = 0; i < p2.lives; i ++) {
            al_draw_bitmap(p2.lives_path, 450 + i * 50, 0, 0);
        }
    }
}

void InitPlayer(player &p) {
    if (p.ID == PLAYER1) {
        p.x = WIDTH / 2 - 150;
        p.y = HEIGHT/2 + 200;
        p.dx = 30;
        p.lives = 5;
        p.bound_x = p.bound_y = 100;
    }
    else if (p.ID == PLAYER2){
        p.x = WIDTH / 2 + 150;
        p.y = HEIGHT/2 + 150;
        p.dx = 30;
        p.lives = 5;
        p.bound_x = p.bound_y = 100;
    }
}

void DrawAbout(void) {
    al_clear_to_color(al_map_rgb(100,100,100));
    
    font = al_load_ttf_font("pirulen.ttf",12,0);
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, 50, ALLEGRO_ALIGN_CENTER, "About");
    
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Made by Kimble Chen");
    
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2 + 60, ALLEGRO_ALIGN_CENTER, "Press 'R' to return");
    al_draw_rectangle(WIDTH/2 - 100, HEIGHT/2 + 50, WIDTH/2 + 100, HEIGHT/2 + 90, al_map_rgb(255, 255, 255), 0);
}

void DrawMenu(void) {
    al_clear_to_color(al_map_rgb(100,100,100));
    font = al_load_ttf_font("pirulen.ttf",12,0);
    
    if (p1.lives > p2.lives) {
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2 - 50, ALLEGRO_ALIGN_CENTER, "Player 1 Wins");
    }
    else {
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2 - 50, ALLEGRO_ALIGN_CENTER, "Player 2 Wins");
    }
    al_draw_rectangle(WIDTH/2 - 120, HEIGHT/2 - 60, WIDTH/2 + 120, HEIGHT/2 - 20, al_map_rgb(255, 255, 255), 0);
    
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "Press 'R' to Restart");
    al_draw_rectangle(WIDTH/2 - 120, HEIGHT/2 - 10, WIDTH/2 + 120, HEIGHT/2 + 30, al_map_rgb(255, 255, 255), 0);
    
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2 + 50, ALLEGRO_ALIGN_CENTER, "Press 'E' to exit");
    al_draw_rectangle(WIDTH/2 - 120, HEIGHT/2 + 40, WIDTH/2 + 120, HEIGHT/2 + 80, al_map_rgb(255, 255, 255), 0);
}

void InitBullet(Bullet bullet[], int size) {
    for (int i = 0; i < size; i ++) {
        if (bullet == bullets1) {
            bullet[i].ID = BULLET1;
            bullet[i].v = 10;
        }
        else if (bullet == bullets2) {
            bullet[i].ID = BULLET2;
            bullet[i].v = -10;
        }
        
        bullet[i].alive = false;
    }
}

void DrawBullet(Bullet bullet[], int size) {
    ALLEGRO_COLOR color;
    
    if (bullet == bullets1) color = al_map_rgb(225, 225, 225);
    else color = al_map_rgb(0, 0, 0);
    
    for (int i = 0; i < size; i ++) {
        if (bullet[i].alive) al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, color);
    }
}

void FireBullet(Bullet bullet[], int size, player &p) {
    for (int i = 0; i < size; i ++) {
        if (!bullet[i].alive) {
            bullet[i].x = p.x + 10;
            bullet[i].y = p.y + 10;
            bullet[i].alive = true;
            break;
        }
    }
}

void UpdateBullet(Bullet bullet[], int size) {
    for (int i = 0; i < size; i ++) {
        if (bullet[i].alive) {
            bullet[i].x += bullet[i].v;
            if (bullet == bullets1 && bullet[i].x > WIDTH) {
                bullet[i].alive = false;
            }
            else if (bullet == bullets2 && bullet[i].x < 0) {
                bullet[i].alive = false;
            }
        }
    }
}

