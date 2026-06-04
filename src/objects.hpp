#pragma once
#include <vector>


template <typename T>
class Objects {
    std::vector<T> objects;
    public:
    Objects() = default;
    Objects(std::initializer_list<T> l) : objects(l) {}

    void add_object(T obj) {
        objects.push_back(obj);
    }

    const std::vector<T>& get_objects() {
        return objects;
    }
    void move() {
        for (T& object : objects) {
            object.move();
        }
    }
};