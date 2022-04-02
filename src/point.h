#pragma once

const int WIDTH = 20;
const int HEIGHT = 8;

struct Point
{
public:
    int x, y;
public:
    Point operator +(const Point&);
    void operator =(const Point&);
    void operator +=(const Point&);
    bool operator ==(const Point&);
    void operator *=(const Point&);

    Point(int x, int y);
    Point();
};

