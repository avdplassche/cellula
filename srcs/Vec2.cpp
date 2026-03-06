#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2(float x_val, float y_val): x(x_val), y(y_val) {}
  

Vec2& Vec2::operator=(const Vec2& other){
    if (this == &other)
        return *this;
    this->x = other.x;
    this->y = other.y;
    return *this;
}


void    Vec2::setValues(float x_val, float y_val) {
    x = x_val;
    y = y_val;
    dist = std::sqrt(x * x + y * y);
}

void    Vec2::normalize() {
    setValues(x / dist, y / dist);
}

void    Vec2::inverse() {
    x *= -1;
    y *= -1;
}
