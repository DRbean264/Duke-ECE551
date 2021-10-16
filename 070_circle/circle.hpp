#include "point.hpp"

class Circle
{
    Point center;
    const double radius;
public:
    Circle(Point p, double r);
    void move(double dx, double dy);
    double intersectionArea(const Circle & otherCircle);    
};
