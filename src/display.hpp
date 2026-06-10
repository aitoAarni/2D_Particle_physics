#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "circle.hpp"
#include <chrono>
#include <thread>
#include <atomic>

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
    Display(WindowSize &window_size) : width(window_size.width), height(window_size.height) {}
    ~Display()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void start_display(Circles &circles, std::atomic<bool> &is_running, int fps = 144)
    {
        initialize();
        display_loop(circles, is_running, fps);
    }

    void display_loop(Circles &circles, std::atomic<bool> &is_running, int fps = 144)
    {
        std::chrono::microseconds frame_time{1'000'000 / fps};
        while (is_running.load())
        {
            auto frame_start = std::chrono::steady_clock().now();
            if (circles.is_updating())
                continue;
            draw_background();
            draw_circles(circles);
            draw_changes();
            std::cout << "frame time: " << "\n";
            std::this_thread::sleep_until(frame_start + frame_time);
        }
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
