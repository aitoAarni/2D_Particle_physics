#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "circle.hpp"
#include "display.hpp"
#include <chrono>
#include <thread>
#include <atomic>
#include "collision_detection.hpp"
#include "collision_resolver.hpp"

class PhysicsEngine
{
    WindowSize window_size;
    Circles circles;

public:
    PhysicsEngine(WindowSize& window_s) : window_size(window_s) {}

    void initialize_game()
    {
        float r = 14;
        circles.add_circle(Circle(900, 200, r, 0, -2, 3));
        circles.add_circle(Circle(800, 300, r, -2, -2, 8));
        circles.add_circle(Circle(700, 500, r, 1, -2, 2));
        circles.add_circle(Circle(600, 1000, r, 2, -2, 5));
        circles.add_circle(Circle(500, 1000, r, 2, -2, 5));
        circles.add_circle(Circle(400, 1000, r, 2, -2, 5));
        circles.add_circle(Circle(300, 1000, r, 2, -2, 5));
        circles.add_circle(Circle(200, 1000, r, 2, -2, 5));
        circles.add_circle(Circle(100, 800, r, 2, -2, 5));
        circles.add_circle(Circle(100, 900, r, 2, -2, 5));
        circles.add_circle(Circle(100, 700, r, 2, -2, 50));
        circles.add_circle(Circle(100, 600, r, 2, -2, 2));
        circles.add_circle(Circle(100, 500, r, 2, -2, 1));
        circles.add_circle(Circle(100, 400, r, 2, -2, 1));
        circles.add_circle(Circle(900, 410, r, 2, -2, 1));
        circles.add_circle(Circle(190, 420, r, 2, -2, 8));
        circles.add_circle(Circle(180, 30, r, 2, -2, 2));
        circles.add_circle(Circle(470, 440, r, 2, -2, 3));
        circles.add_circle(Circle(1600, 450, r, 2, -2, 5));
        circles.add_circle(Circle(1050, 460, r, 2, -2, 5));
        circles.add_circle(Circle(840, 470, r, 2, -2, 5));
        circles.add_circle(Circle(30, 480, r, 2, -2, 7));
        circles.add_circle(Circle(320, 490, r, 2, -2, 5));
        circles.add_circle(Circle(510, 400, r, 2, -2, 5));
    }

    Circles& get_circles() {
        return circles;
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
            resolve_border_collision(circles[a_index], border_direction, window_size);
        }
    }

    void loop(int tick_rate, std::atomic<bool>& is_running, int ticks_rate = 128)
    {
        SDL_Event event;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        auto tick_dealy = std::chrono::milliseconds(1'000'000 / tick_rate);
        while (is_running)
        {

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    is_running = false;
                }
            }
            auto frame_start = std::chrono::steady_clock::now();
            circles.move();
            handle_collisions();
            circles.update_complete();
            std::this_thread::sleep_until(frame_start + std::chrono::milliseconds(3));
        }
    }
};