#pragma once

const int WIDTH = 20;
const int HEIGHT = 8;
const int FAKEUP = 123;
const int FAKEDOWN = 125;

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

