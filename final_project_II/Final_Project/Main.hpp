//
//  Main.hpp
//  Final_Project
//
//  Created by Kimbo Chen on 6/21/18.
//  Copyright © 2018 K-Machina. All rights reserved.
//

#ifndef Main_hpp
#define Main_hpp

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
#include <time.h>

#define WIN_W 2048.0
#define WIN_H 1366.0
#define CARD_W 400.0
#define CARD_H 500.0
#define CARD_R 60.0
#define SHELF_H 650.0
#define SHELF_W 1638.4
#define DOCK_X(i) SHELF_W * (2 * i + 1)/4 - CARD_W / 2
#define DOCK_Y (VIEWER_H - CARD_H) / 2
#define SHELF_X(i) (SHELF_W / 4 - CARD_W) / 2 + SHELF_W * i/4
#define SHELF_Y VIEWER_H + (SHELF_H - CARD_H) / 2

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define RED al_map_rgb(204, 22, 49)
#define GRAY al_map_rgb(128, 128, 128)

#define min(a, b) (a < b)? a : b
#define max(a, b) (a > b)? a : b

const float VIEWER_H = WIN_H - SHELF_H;
const float MENU_W = WIN_W - SHELF_W;
const float FPS = 60.0;

#endif /* Main_hpp */
