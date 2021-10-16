#include "circle.hpp"
#include <cmath>
using namespace std;

Circle::Circle(Point p, double r)
    : center(p), radius(r) {}

void Circle::move(double dx, double dy) {
    center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
    double r1 = radius;
    double r2 = otherCircle.radius;
    double d = center.distanceFrom(otherCircle.center);
    
    if (d >= r1 + r2 || r1 == 0 || r2 == 0) return 0;
    else if (d + r2 <= r1 || d + r1 <= r2) {
        return r2 > r1 ? M_PI * r1 * r1 : M_PI * r2 * r2;
    }
    
    double cosa1 = (- r2 * r2 + r1 * r1 + d * d) / (2 * r1 * d);
    double cosa2 = (- r1 * r1 + r2 * r2 + d * d) / (2 * r2 * d);
    double h = r1 * sqrt(1 - cosa1 * cosa1);

    double sSquare = d * h;
    double sFan1 = r1 * r1 * acos(cosa1);
    double sFan2 = r2 * r2 * acos(cosa2);

    return sFan1 + sFan2 - sSquare;
}
