#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "circle.hpp"

void fill_circle(SDL_Renderer *renderer, const Circle &circle)
{
    float r_pow_2{circle.get_radius() * circle.get_radius()};
    float x_pow_2{circle.get_x() * circle.get_x()};
    float y_pow_2 = {circle.get_y() * circle.get_y()};
    float b{2 * circle.get_x()};
    float b_pow_2{b * b};
    for (int y{static_cast<int>(std::round(circle.get_y() - circle.get_radius()))}; y <= circle.get_y() + circle.get_radius(); y++)
    {
        int c = x_pow_2 + (circle.get_y() - y) * (circle.get_y() - y) - r_pow_2;
        int x_0 = b + std::sqrt(b_pow_2 - 4 * c);
        int x_1 = b - std::sqrt(b_pow_2 - 4 * c);
        SDL_RenderDrawLine(renderer, std::lround(std::min(x_0, x_1) / 2), y, std::lround(std::max(x_0, x_1) / 2), y);
    }
}

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

    void draw_background()
    {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void draw_circle(const Circle &circle)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        fill_circle(renderer, circle);
    }

    void draw_circles(Circles &circles)
    {
        for (const auto &circle : circles.get_circles())
        {
            draw_circle(circle);
        }
    }

    // swap buffers to push the frame to the monitor
    void draw_changes()
    {
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
            "C++ Physics Sandbo",
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
