#include "ball.h"
#include "paddle.h"

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

void Ball::collision(const Paddle& left, const Paddle& right)
{
    // paddle collision
    if (Ball::location == left.location || Ball::location == right.location)
    {
        Ball::velocity *= Point(-1, 1);
    }

    // top or bottom collision
    if (Ball::location.y == 0 || Ball::location.y == 7)
    {
        Ball::velocity *= Point(1, -1);
    }
}