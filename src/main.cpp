#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <string>
#include "paddle.h"
#include "ball.h"
#include "point.h"

void update(char picture[HEIGHT][WIDTH], bool init);
void draw(char picture[HEIGHT][WIDTH]);
void listen(std::string& keyboardInput);
void handleUserInput(const std::string& inputs, int& length, Paddle& left, Paddle& right);

void fixTerminalOnExit(int signal);

int main()
{
    bool running = true;
    char picture[HEIGHT][WIDTH];
    std::string keyboardInput = "////";
    int inputLength, framePassed = 0;
    
    // fix terminal on keyboard interupt
    std::signal(SIGINT, fixTerminalOnExit);

    // initiate paddles and picture
    Paddle leftPaddle(Point(0, 4)), rightPaddle(Point(19, 4));
    update(picture, true);
    std::thread userInput(listen, std::ref(keyboardInput));

    // game loop
    while (running)
    {
        framePassed++;
        std::cout << "frame " << framePassed << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        handleUserInput(keyboardInput, inputLength, leftPaddle, rightPaddle);
        draw(picture);

    }

    // closing
    system("stty cooked");
}

void update(char picture[HEIGHT][WIDTH], bool init = false)
{
    // initiate array of space characters
    if (init)
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                picture[i][j] = ' ';
            }
        }
    }

}


void draw(char picture[HEIGHT][WIDTH])
{
    // clear console
    system("clear");
    system("stty cooked");

    // draw everything onto the screen
    for (int i = 0; i < WIDTH + 2; i++)
        std::cout << '=';
    std::cout << '\n';
    for (int i = 0; i < HEIGHT; i++)
    {
        std::cout << '|';
        for (int j = 0; j < WIDTH; j++)
            std::cout << picture[i][j];
        std::cout << "|\n";
    }
    for (int i = 0; i < WIDTH; i++)
        std::cout << '=';
    std::cout << '\n';

    system("stty raw");
}

void listen(std::string& keyboardInput)
{   
    system("stty raw");

    for (int i = 0; true; i++)
    {
        if (i == 4)
        {
            i = 0;
            keyboardInput = "////";
        }
        keyboardInput[i] = getchar();
    }
}

void handleUserInput(const std::string& inputs, int& length, Paddle& leftPaddle, Paddle& rightPaddle)
{
    // modify the velocities of paddles
    for (int i = 0; i < 2; i++)
    {
        switch (inputs[i])
        {        
            case 'w' :
                leftPaddle.velocity.y = 1;
                break;
            case 's' :
                leftPaddle.velocity.y = -1;
                break;
            case 'u' : // fill with up arrow key
                rightPaddle.velocity.y = 1;
                break;
            case 'd' : // fill with down arrow key
                rightPaddle.velocity.y = -1;
                break;
            case 'c' :
                fixTerminalOnExit(0);
                break;
        }
        std::cout << "User inputed: " << inputs[i] << std::endl;
    }
}

void fixTerminalOnExit(int signal)
{
    std::cout << "Program exiting! :)" << std::endl;
    system("stty cooked");
    exit(0);
}