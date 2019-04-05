#ifndef header_hpp
#define header_hpp

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GAME_TERMINATE -1

enum ID {PLAYER1, PLAYER2, BULLET1, BULLET2};
enum FRAME {START, ABOUT, GAME, MENU};
enum KEYS {LEFT, RIGHT, JUMP, SHOOT};
bool keys[4] = {false, false, false, false};

typedef struct {
    int ID;
    double x, y;
    double dx, dy;
    double bound_x, bound_y;
    int lives;
    bool keys[4] = {false, false, false, false};
    ALLEGRO_BITMAP *lives_path = NULL;
    ALLEGRO_BITMAP *image_path = NULL;
} player;

typedef struct {
    int ID;
    int x, y, v;
    bool alive;
} Bullet;

const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_BULLETS = 7;
const double BOUND_L1 = 0;
const double BOUND_R1 = 280;
const double BOUND_L2 = WIDTH / 2;
const double BOUND_R2 = 730;
const double FPS = 60;
bool redraw = true;
int frame = START;
player p1, p2;
Bullet bullets1[NUM_BULLETS], bullets2[NUM_BULLETS];

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

void DrawStart();
void DrawAbout();
void DrawMenu();
void InitPlayer(player &p);
void DrawPlayer(player &p);
void Jump(player &p);
void MoveRight(player &p);
void MoveLeft(player &p);
void InitBullet(Bullet bullet[], int size);
void DrawBullet(Bullet bullet[], int size);
void FireBullet(Bullet bullet[], int size, player &p);
void UpdateBullet(Bullet bullet[], int size);
void CollideBullet(Bullet bullet[], int size, player &p);

#endif
