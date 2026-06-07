#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "circle.hpp"
#include "display.hpp"
#include <chrono>
#include <thread>
#include "collision_detection.hpp"
#include "collision_resolver.hpp"

class Game
{
    Display display;
    WindowSize window_size;
    Circles circles;

public:
    Game(int width, int height) : display(width, height), window_size(width, height) {}

    void initialize_game()
    {
        circles.add_circle(Circle(1000, 500, 5, -1, -2, 1));
        circles.add_circle(Circle(900, 200, 5, 0, -2, 3));
        circles.add_circle(Circle(800, 300, 5, -2, -2, 8));
        circles.add_circle(Circle(700, 500, 5, 1, -2, 2));
        circles.add_circle(Circle(600, 1000, 5, 2, -2, 5));
        circles.add_circle(Circle(500, 1000, 5, 2, -2, 5));
        circles.add_circle(Circle(400, 1000, 5, 2, -2, 5));
        circles.add_circle(Circle(300, 1000, 5, 2, -2, 5));
        circles.add_circle(Circle(200, 1000, 5, 2, -2, 5));
        circles.add_circle(Circle(100, 800, 5, 2, -2, 5));
        circles.add_circle(Circle(100, 900, 5, 2, -2, 5));
        circles.add_circle(Circle(100, 700, 5, 2, -2, 50));
        circles.add_circle(Circle(100, 600, 5, 2, -2, 2));
        circles.add_circle(Circle(100, 500, 5, 2, -2, 1));
        circles.add_circle(Circle(100, 400, 5, 2, -2, 1));
        circles.add_circle(Circle(900, 410, 5, 2, -2, 1));
        circles.add_circle(Circle(190, 420, 5, 2, -2, 8));
        circles.add_circle(Circle(180, 430, 5, 2, -2, 2));
        circles.add_circle(Circle(170, 440, 5, 2, -2, 3));
        circles.add_circle(Circle(160, 450, 5, 2, -2, 5));
        circles.add_circle(Circle(150, 460, 5, 2, -2, 5));
        circles.add_circle(Circle(140, 470, 5, 2, -2, 5));
        circles.add_circle(Circle(130, 480, 5, 2, -2, 7));
        circles.add_circle(Circle(120, 490, 5, 2, -2, 5));
        circles.add_circle(Circle(110, 400, 5, 2, -2, 5));
    }

    void handle_collisions()
    {
        for (int a_index = 0; a_index < circles.get_circles().size(); a_index++)
        {
            for (int b_index = a_index + 1; b_index <= circles.get_circles().size(); b_index++)
            {
                if (collision_detection(circles[a_index], circles[b_index]))
                    resolve_collision(circles[a_index], circles[b_index]);
            }
            Direction border_direction = border_collision(circles[a_index], window_size);
            if (border_direction == Direction::Undefined)
                continue;
            resolve_border_collision(circles[a_index], border_direction);
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
            handle_collisions();
            display.draw_background();
            display.draw_circles(circles);
            display.draw_changes();
            std::this_thread::sleep_until(frame_start + std::chrono::milliseconds(3));
        }
    }
};