#include <SDL2/SDL.h>
#include <iostream>
#include "game.hpp"

int main(int argc, char *args[])
{
    Game game(3200, 1300);
    game.initialize_game();
    game.loop();
    return 0;
}