class Point
{
    double x;
    double y;
    
public:
    Point();
    void move(double dx, double dy);
    double distanceFrom(const Point &p);    
};
