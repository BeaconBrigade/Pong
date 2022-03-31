#pragma once
#include "point.h"

class Paddle
{
private:
    Point location;
public:
    Paddle(Point& location);
    void move(char direction);
};