#pragma once
#include "point.h"

class Paddle
{
private:
    Point velocity;
public:
    Point location;
    Paddle(Point location);
    void move(char direction);
};