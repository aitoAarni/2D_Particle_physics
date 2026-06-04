#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "circle.hpp"
#include "objects.hpp"

class Display
{
    int width;
    int height;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

public:
    Display(int w, int h) : width(w), height(h) {}
    ~Display()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw_background() {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    } 

    void draw_circle(const Circle& circle) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        fill_circle(renderer, circle);
    }

    void draw_objects(Objects<Circle>& objects) {
        for (const auto& circle : objects.get_objects()) {
            draw_circle(circle);
        }
    }

        // swap buffers to push the frame to the monitor
    void draw_changes() {
        SDL_RenderPresent(renderer);
    }

    bool initialize()
    {

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
            return -1;
        }

        window = SDL_CreateWindow(
            "C++ Physics Sandbox",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
            SDL_Quit();
            return -1;
        }

        renderer = SDL_CreateRenderer(
            window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr)
        {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
        }

        return true;
    }
};