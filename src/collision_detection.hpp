#pragma once
#include "circle.hpp"
#include <cmath>
#include <iostream>

bool collision_detection(const Circle &a, const Circle &b)
{
    float x_delta = a.get_x() - b.get_x();
    float y_delta = a.get_y() - b.get_y();
    float distance = std::sqrt(x_delta * x_delta + y_delta * y_delta);
    if (distance <= a.get_radius() + b.get_radius())
    {
        std::cout << "aaaa hittiiiing aaaaa\n";
    }
    return distance <= a.get_radius() + b.get_radius();
}
