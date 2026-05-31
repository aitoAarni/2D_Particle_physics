#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window *window = nullptr;

SDL_Surface *screen_surface = nullptr;

SDL_Surface *image = nullptr;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            screen_surface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    image = SDL_LoadBMP( "images/dots.bmp" );
    if( image == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close() {
    SDL_FreeSurface(image);
    image = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}