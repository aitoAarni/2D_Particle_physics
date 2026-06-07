#include <SDL2/SDL.h>
#include <iostream>
#include "physics_engine.hpp"
#include <atomic>
#include "display.hpp"

int main(int argc, char *args[])
{
    WindowSize window_size(3200, 1300);
    PhysicsEngine simulation(window_size);
    Display display(window_size);

    std::atomic<bool> is_running {true};
    simulation.initialize_game();
    display.initialize();
        
    simulation.loop(128, is_running);

    return 0;
}