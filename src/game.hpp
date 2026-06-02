#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "circle.hpp"
#include "display.hpp"

class Game
{
    Display display;
    std::vector<Circle> circles;

public:
    Game(int width, int height) : display(Display(width, height)) { circles.emplace_back(600, 400, 100); }

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
                display.draw_background();
                display.draw_circle(circles.front());
                display.draw_changes();
            }
        }
    }
};