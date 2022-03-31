#pragma once

struct Point
{
public:
    int x, y;

    Point operator +(const Point&);
    void operator =(const Point&);
    void operator +=(const Point&);

    Point(int x, int y);
    Point();
};

