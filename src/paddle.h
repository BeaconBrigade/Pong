#pragma once
#include "point.h"

class Paddle
{
public:
    Point velocity;
    Point location;
    Paddle(Point location);
    void move(char direction);
};