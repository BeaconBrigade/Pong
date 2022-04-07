#pragma once
#include "point.h"
#include "paddle.h"

enum whoWon
{
    noWin, leftWin, rightWin
};

class Ball
{
public:
    Point velocity;
    Point location;
public:
    whoWon checkGameEnd() const;
    Ball(Point& newLocation, Point& newVelocity);
    whoWon collision(const Paddle& left, const Paddle& right, int& leftScore, int& rightScore);
    void move();
};