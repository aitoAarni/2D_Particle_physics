#pragma once
#include "circle.hpp"
#include "structs.hpp"
#include <cmath>

Vector contact_normal(Circle &a, Circle &b)
{
    float y{b.get_y() - a.get_y()};
    float x{b.get_x() - a.get_x()};
    float dist{std::hypot(x, y)};
    return {x / dist, y / dist};
}

float closing_velocity(Circle &a, Circle &b)
{
    auto velocity_delta =  a.get_velocity() - b.get_velocity();
    std::cout << "velocity_delta: " << velocity_delta << "\n";
    auto contact_norm_vec = contact_normal(a, b);
    std::cout << "contact_norm_vec: " << contact_norm_vec << "\n";
    return velocity_delta * contact_norm_vec;
}