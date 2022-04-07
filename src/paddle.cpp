#include "paddle.h"

Paddle::Paddle(Point newLocation) : location(newLocation), velocity(Point(0, 0)) {}

void Paddle::move()
{
    // up
    if (Paddle::velocity.y == -1 && Paddle::location.y > 0)
        Paddle::location += Paddle::velocity;

    // down
    else if (Paddle::velocity.y == 1 && Paddle::location.y + 2 < HEIGHT - 1)
        Paddle::location += Paddle::velocity;
}