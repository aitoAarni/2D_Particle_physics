#include <vector>
#include <SDL2/SDL.h>

class Circle {
    public:
    int x;
    int y;
    int radius;
    Circle(int x_initial, int y_initial, int r) : x(x_initial), y(y_initial), radius(r) {}
};

void fill_circle(SDL_Renderer* renderer, Circle& circle) {
    
    for (int y = circle.y-circle.radius; y <= circle.y + circle.radius; y++) {
        
    }
}