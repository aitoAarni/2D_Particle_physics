#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <format>
// #include <algorithm>

class Circle {
    public:
    int x;
    int y;
    int radius;
    Circle(int x_initial, int y_initial, int r) : x(x_initial), y(y_initial), radius(r) {}
};

void fill_circle(SDL_Renderer* renderer, Circle& circle) {
    int r_pow_2 = circle.radius * circle.radius;
    int x_pow_2 = circle.x*circle.x;
    int y_pow_2 = circle.y*circle.y;
    int b = 2 * circle.x;
    int b_pow_2 = b * b;
    for (int y = circle.y-circle.radius; y <= circle.y + circle.radius; y++) {
        int c = x_pow_2 + (circle.y - y) * (circle.y - y) - r_pow_2;
        int x_0 = b + std::sqrt(b_pow_2 - 4*c);
        int x_1 = b - std::sqrt(b_pow_2 - 4*c);
        std::cout << std::format("line from ({}, {}) to ({}, {})\n", std::min(x_0, x_1), y, std::max(x_0, x_1), y);
        SDL_RenderDrawLine(renderer, std::min(x_0, x_1)/2, y, std::max(x_0, x_1)/2, y);
    }
}