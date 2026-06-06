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
