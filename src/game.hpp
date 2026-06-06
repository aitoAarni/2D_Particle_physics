#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "circle.hpp"
#include "display.hpp"
#include <chrono>
#include <thread>
#include "collision_detection.hpp"

class Game
{
    Display display;
    Circles circles;

public:
    Game(int width, int height) : display(width, height) {}

    void initialize_game()
    {
        circles.add_circle(Circle(600, 400, 100));
        circles.add_circle(Circle(1000, 400, 50, -5, 5));
    }

    void update_collisions()
    {
        for (int a_index = 0; a_index <= circles.get_circles().size(); a_index++)
        {
            for (int b_index = a_index + 1; b_index <= circles.get_circles().size(); b_index++)
            {
                collision_detection(circles[a_index], circles[b_index]);
            }
        }
    }

    void loop()
    {
        display.initialize();
        bool isRunning = true;
        SDL_Event event;
        while (isRunning)
        {

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    isRunning = false;
                }
            }
            auto frame_start = std::chrono::steady_clock::now();
            circles.move();
            update_collisions();
            display.draw_background();
            display.draw_circles(circles);
            display.draw_changes();
            std::this_thread::sleep_until(frame_start + std::chrono::milliseconds(250));
        }
    }
};