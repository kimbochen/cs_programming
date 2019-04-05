//
//  global.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/7/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef global_hpp
#define global_hpp

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <utility>
#include <list>
#include <ctime>
#include <cmath>

#define WINDOW_WIDTH 2048.0
#define WINDOW_HEIGHT 1366.0
#define BLOCK_WIDTH 500.0
#define BLOCK_HEIGHT 500.0
#define BLOCK_RADIUS 40.0
#define SHELF_H 800.0
#define SHELF_W 1638.4
#define DOCK_X(i) SHELF_W * (2 * i + 1)/4 - BLOCK_WIDTH / 2
#define DOCK_Y (VIEWER_H - BLOCK_HEIGHT) / 2

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define RED al_map_rgb(204, 22, 49)
#define GRAY al_map_rgb(128, 128, 128)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) (a < b)? a : b
#define max(a, b) (a > b)? a : b

const float VIEWER_H = WINDOW_HEIGHT - SHELF_H;
const float MENU_W = WINDOW_WIDTH - SHELF_W;
const float FPS = 60.0;
extern int frames;

enum STATE {START, PROLOGUE, GAME, VICTORY, FAIL, PAUSE};
//enum CASE {STAGE1, STAGE2, EXTRA};

#endif /* global_hpp */
