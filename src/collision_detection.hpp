#pragma once
#include "circle.hpp"
#include <cmath>
#include <iostream>
#include "structs.hpp"

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

Direction border_collision(const Circle &circle, const WindowSize &window)
{

    // doesn't account for hitting a corner (2 sides at one time)
    if (circle.get_y() - circle.get_radius() <= 0)
        return Direction::Top;
    else if (circle.get_x() + circle.get_radius() >= window.width)
        return Direction::Right;
    else if (circle.get_y() + circle.get_radius() >= window.height)
        return Direction::Bottom;
    else if (circle.get_x() - circle.get_radius() <= 0)
        return Direction::Left;

    return Direction::Undefined;
}