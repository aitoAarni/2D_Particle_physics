#pragma once
#include <iostream>

struct Vector
{
    float x;
    float y;

    Vector operator-(Vector &other)
    {
        return {x - other.x, y - other.y};
    }
    
    Vector operator+(Vector &other)
    {
        return {x + other.x, y + other.y};
    }
    
    float operator*(Vector &other)
    {
        return x * other.x + y * other.y;
    }
    
    Vector operator*(float scalar)
    {
        return {x * scalar, y * scalar};
    }
    
    Vector operator-()
    {
        return {-x, -y};
    }
};

std::ostream &operator<<(std::ostream &os, Vector vec)
{
    return os << "x: " << vec.x << ", y: " << vec.y;
}
