#pragma once
#include "point.h"
#include "paddle.h"

enum whoWon
{
    noWin, leftWin, righWin
};

class Ball
{
private:
    Point velocity;
public:
    Point location;
    whoWon checkGameEnd();
    Ball(Point& newLocation, Point& newVelocity);
    void move();
    void collision(const Paddle& left, const Paddle& right);
};