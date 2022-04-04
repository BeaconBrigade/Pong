#pragma once
#include "point.h"

class Paddle
{
public:
    Point velocity;
    Point location;
public:
    Paddle(Point location);
    void move();
};