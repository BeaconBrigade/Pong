#pragma once

const int WIDTH = 20;
const int HEIGHT = 8;
const char* const SQUARE = "█";

struct Point
{
public:
    int x, y;

    Point operator +(const Point&);
    void operator =(const Point&);
    void operator +=(const Point&);
    bool operator ==(const Point&);
    void operator *=(const Point&);

    Point(int x, int y);
    Point();
};

