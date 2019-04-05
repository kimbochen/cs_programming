//
//  MyTower.h
//  mini_project_2
//
//  Created by Kimbo Chen on 6/5/18.
//  Copyright © 2018 Kimbo Chen. All rights reserved.
//

#ifndef MyTower_h
#define MyTower_h

#include "Tower.h"

class MyTower : public Tower
{
public:
    MyTower (int mouse_x, int mouse_y) : Tower(mouse_x, mouse_y)
    {
        type = MYTOWER;
        
        circle->r = 80;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./Tower/MyTower.png");
        attack_img = al_load_bitmap("./Tower/Arcane_Beam.png");
    }
    
    int getWidth() override { return TowerWidth[MYTOWER]; }
    int getHeight() override { return TowerHeight[MYTOWER]; }
};

#endif /* MyTower_h */
