#include <SDL2/SDL.h>
#include <iostream>
#include "tools.hpp"
#include "circle.hpp"



int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "C++ Physics Sandbox",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1200, 1000,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    bool isRunning = true;
    SDL_Event event;
    Circle circle(600, 500, 50);

    while (isRunning) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        fill_circle(renderer, circle);

        // swap buffers to push the frame to the monitor
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}