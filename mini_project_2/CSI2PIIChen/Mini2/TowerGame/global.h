#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 800
#define window_height 600
#define field_width 600
#define field_height 600

#define Num_TowerType 6
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int TowerRadius[];
extern char TowerClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];
extern int windowState;

enum {ARCANE = 0, ARCHER, CANON, POISON, STORM, MYTOWER};
enum {WOLF = 0, WOLFKNIGHT, DEMONNIJIA, CAVEMAN};
enum STATE {STATE_START, STATE_GAME, STATE_PAUSE};

#endif // GLOBAL_H_INCLUDED
