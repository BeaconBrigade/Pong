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
    Point location;
    Point velocity;
public:
    whoWon checkGameEnd();
    Ball(Point& newLocation, Point& newVelocity);
    void move();
    bool collision(Paddle& left, Paddle& right);

};