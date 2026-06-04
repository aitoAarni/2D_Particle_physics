#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "circle.hpp"
#include "display.hpp"
#include "objects.hpp"
#include <chrono>
#include <thread>

class Game
{
    Display display;
    Objects<Circle> objects;

public:
    Game(int width, int height) : display(width, height) {}

    void initialize_game() {
        objects.add_object(Circle(600, 400, 100)); 
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
            objects.move();
            display.draw_background();
            display.draw_objects(objects);
            display.draw_changes();
            std::this_thread::sleep_until(frame_start + std::chrono::milliseconds(250));
        }
    }
};