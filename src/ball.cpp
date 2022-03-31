#include "ball.h"

Ball::Ball(Point& newPosition, Point& newVelocity)
{
    Ball::location = newPosition;
    Ball::velocity = newVelocity;
}

whoWon Ball::checkGameEnd()
{
    if (Ball::location.x == 0)
        return righWin;
    else if (Ball::location.x == 19)
        return leftWin;
    return noWin;
}