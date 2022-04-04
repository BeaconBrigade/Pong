#pragma once
#include "point.h"
#include "paddle.h"

enum whoWon
{
    noWin, leftWin, righWin
};

class Ball
{
public:
    Point velocity;
    Point location;
public:
    whoWon checkGameEnd();
    Ball(Point& newLocation, Point& newVelocity);
    void collision(const Paddle& left, const Paddle& right, int& leftScore, int& rightScore);
    void move();
};