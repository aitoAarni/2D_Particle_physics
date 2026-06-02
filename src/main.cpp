#include <SDL2/SDL.h>
#include <iostream>
#include "game.hpp"

int main(int argc, char *args[])
{
    Game game(1920, 1080);
    game.loop();

    return 0;
}