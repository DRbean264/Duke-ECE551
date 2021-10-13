#include "vector.hpp"

#include <cmath>
#include <cstdio>
using std::sqrt;
using std::printf;

/* write your class implementation in this file
 */
Vector2D::Vector2D() : x(0), y(0) {
}

Vector2D::Vector2D(int x_init, int y_init) : x(x_init), y(y_init) {
}

double Vector2D::getMagnitude() const {
    return sqrt(x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D &rhs) const {
    Vector2D newVec;
    newVec.initVector(x + rhs.x, y + rhs.y);
    return newVec;
}

Vector2D &Vector2D::operator+=(const Vector2D &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

double Vector2D::dot(const Vector2D &rhs) const {
    return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
    printf("<%.2f, %.2f>", x, y);
}
