#include "point.h"

Point Point::operator +(const Point& a) const
{
    return Point(x + a.x, y + a.y);
}

void Point::operator +=(const Point& a)
{
    Point::x = Point::x + a.x;
    Point::y = Point::y + a.y;
}

void Point::operator =(const Point& a)
{
    Point::x = a.x;
    Point::y = a.y;
}

Point::Point(int newX, int newY) : x(newX), y(newY) {}

bool Point::operator ==(const Point& a)
{
    return (Point::x == a.x && Point::y == a.y);
}

void Point::operator *=(const Point& a)
{
    Point::x *= a.x;
    Point::y *= a.y;
}

Point::Point() : x(0), y(0) {}