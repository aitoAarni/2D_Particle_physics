#include <SDL2/SDL.h>
#include "tools.hpp"

int main(int argc, char *args[])
{
    if (!init())
        return 0;
    if (!loadMedia())
        return 0;
    SDL_BlitSurface(image, NULL, screen_surface, NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
    close();
}