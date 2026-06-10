#include <SDL2/SDL.h>
#include <iostream>
#include "physics_engine.hpp"
#include <atomic>
#include "display.hpp"
#include <thread>

int main(int argc, char *args[])
{
    WindowSize window_size(3200, 1300);
    PhysicsEngine simulation(window_size);
    Display display(window_size);

    std::atomic<bool> is_running {true};
    simulation.initialize_game();
        
    std::jthread display_thread(&Display::start_display, &display, std::ref(simulation.get_circles()), std::ref(is_running), 144);
    simulation.loop(128, is_running);
    display_thread.join();

    return 0;
}