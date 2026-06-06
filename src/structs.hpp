#pragma once
#include <iostream>

struct Vector
{
    float x;
    float y;
};

std::ostream &operator<<(std::ostream &os, Vector vec)
{
    return os << "x: " << vec.x << ", y: " << vec.y;
}

Vector operator-(Vector &a, Vector &b)
{
    return {a.x - b.x, a.y - b.y};
}

Vector operator+(Vector &a, Vector &b)
{
    return {a.x + b.x, a.y + b.y};
}

float operator*(Vector &a, Vector &b)
{
    return a.x * b.x + a.y * b.y;
}

Vector operator*(Vector &vec, float scalar)
{
    return {vec.x * scalar, vec.y * scalar};
}

Vector operator-(const Vector &vec)
{
    return {-vec.x, -vec.y};
}