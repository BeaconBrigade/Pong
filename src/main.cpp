#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "paddle.h"
#include "ball.h"

const int WIDTH = 20;
const int HEIGHT = 8;
const char* SQUARE = "█";

void update(char picture[HEIGHT][WIDTH], bool init);
void draw(char picture[HEIGHT][WIDTH]);

int main()
{
    bool finished = false, running = true;
    char picture[HEIGHT][WIDTH];
    update(picture, true);

    while (running)
    {
        draw(picture);
    }
}

void update(char picture[HEIGHT][WIDTH], bool init = false)
{
    // initiate array of space characters
    if (init)
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
                picture[i][j] = ' ';
        }
    }

}


void draw(char picture[HEIGHT][WIDTH])
{
    // clear console
    system("clear");

    // draw everything onto the screen
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            std::cout << picture[i][j];
        std::cout << std::endl;
    }
}

char listen(bool& finished)
{
    char x;
    std::cin >> x;

    finished = true;
    return x;
}