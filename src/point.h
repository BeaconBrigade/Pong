#pragma once

const int WIDTH = 30;
const int HEIGHT = 15;
const int FAKEUP = 123;
const int FAKEDOWN = 125;

struct Point
{
public:
    int x, y;
public:
    Point operator +(const Point&) const;
    void operator =(const Point&);
    void operator +=(const Point&);
    bool operator ==(const Point&);
    void operator *=(const Point&);

    Point(int x, int y);
    Point();
};

