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
void listen(bool& finished, std::string& keyboardInput);
void handleUserInput(const std::string& inputs);


int main()
{
    bool finished = true, running = true;
    char picture[HEIGHT][WIDTH];
    std::string keyboardInput;

    update(picture, true);

    // game loop
    while (running)
    {
        if (finished)
        {
            std::thread userInput(listen, std::ref(finished), std::ref(keyboardInput));

            handleUserInput(keyboardInput);

            userInput.join();
            finished = false;
            keyboardInput = "";
        }



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

void listen(bool& finished, std::string& keyboardInput)
{
    // read keyboard input \\
    finished = true;
}

void handleUserInput(const std::string& inputs, Paddle& leftPaddle, Paddle& rightPaddle)
{
    // modify the velocities of paddles
    for (int i = 0; i < 2; i++)
    {
        if (inputs[i] == 'w')
            leftPaddle.velocity.y = 1;
        else if (inputs[i] == 's')
            leftPaddle.velocity.y = -1;
        else if (inputs[i] == '')
    }
}