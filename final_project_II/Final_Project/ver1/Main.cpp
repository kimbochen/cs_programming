#include "GameWindow.hpp"
#include <allegro5/allegro.h>

int main(int argc, char **argv)
{
    GameWindow *Game= new GameWindow();
    
    Game -> game_play();
    delete Game;
    
    return 0;
}
