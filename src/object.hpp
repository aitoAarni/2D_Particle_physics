#pragma once
#include "structs.hpp"

class Object
{
protected:
    Vector velocity;

public:
    Object(float x_vel = 0, float y_vel = 0)
        : velocity(x_vel, y_vel) {}

    Vector &get_velocity()
    {
        return velocity;
    }
    void set_velocity(Vector vel)
    {
        velocity = vel;
    }
};
