#pragma once

const int WIDTH = 50;
const int HEIGHT = 18;
const int FAKEUP = '{';
const int FAKEDOWN = '}';
const int FPS = 12;
const int DELAY = 1000 / FPS;

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
public:
    Point(int x, int y);
    Point();
};

