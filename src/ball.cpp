#include "ball.h"
#include "paddle.h"

Ball::Ball(Point &newPosition, Point &newVelocity)
    : location(newPosition), velocity(newVelocity) {}

whoWon Ball::checkGameEnd() const {
    if (Ball::location.x == 0)
        return rightWin;
    else if (Ball::location.x == WIDTH - 1)
        return leftWin;
    return noWin;
}

whoWon Ball::collision(const Paddle &left, const Paddle &right, int &leftScore,
                       int &rightScore) {
    // paddle collision
    // left
    if (Ball::location.x == 0) {
        if (Ball::location == left.location ||
            Ball::location == left.location + Point(0, 1) ||
            Ball::location == left.location + Point(0, 2)) {
            Ball::velocity *= Point(-1, 1);
            leftScore++;
        } else
            return rightWin;
    }
    // right
    if (Ball::location.x == WIDTH - 1) {
        if (Ball::location == right.location ||
            Ball::location == right.location + Point(0, 1) ||
            Ball::location == right.location + Point(0, 2)) {
            Ball::velocity *= Point(-1, 1);
            rightScore++;
        } else
            return leftWin;
    }

    // top or bottom collision
    if (Ball::location.y == 0 || Ball::location.y == HEIGHT - 1) {
        Ball::velocity *= Point(1, -1);
    }

    return noWin;
}

void Ball::move() { Ball::location += Ball::velocity; }
