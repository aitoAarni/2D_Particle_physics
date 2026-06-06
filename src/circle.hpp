#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <format>
#include "structs.hpp"

class Circle
{
    Vector velocity;
    float weight;
    float x;
    float y;
    float radius;

public:
    Circle(float x_initial, float y_initial, float r, float x_vel = 5, float y_vel = 5, float w = 2)
        : x(x_initial), y(y_initial), radius(r), velocity(x_vel, y_vel), weight(w) {}

    void move()
    {
        x += velocity.x;
        y += velocity.y;
    }
    float get_x() const
    {
        return x;
    }
    float get_y() const
    {
        return y;
    }
    float get_radius() const
    {
        return radius;
    }
    float get_weight() const
    {
        return weight;
    }
    Vector &get_velocity()
    {
        return velocity;
    }
    void set_y(float new_y)
    {
        y = new_y;
    }
    void set_x(float new_x)
    {
        x = new_x;
    }
    void set_radius(float r)
    {
        radius = radius;
    }
    void set_weight(float w)
    {
        weight = w;
    }
    void set_velocity(Vector vel)
    {
        std::cout << "old vel: " << velocity << ", new_vel: " << vel << "\n";
        velocity = vel;
    }
};

class Circles
{
    std::vector<Circle> circles;

public:
    Circles() = default;
    Circles(std::initializer_list<Circle> l) : circles(l) {}

    void add_circle(Circle obj)
    {
        circles.push_back(obj);
    }

    const std::vector<Circle> &get_circles()
    {
        return circles;
    }

    Circle &operator[](int index)
    {
        return circles[index];
    }
    void move()
    {
        for (Circle &circle : circles)
        {
            circle.move();
        }
    }
};