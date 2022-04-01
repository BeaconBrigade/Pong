#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <string>
#include "paddle.h"
#include "ball.h"

const int WIDTH = 20;
const int HEIGHT = 8;
const char* SQUARE = "█";

void update(char picture[HEIGHT][WIDTH], bool init);
void draw(char picture[HEIGHT][WIDTH]);
void listen(bool& finished, std::string& keyboardInput, int& length);
void handleUserInput(const std::string& inputs, int& length, Paddle& left, Paddle& right);

void fixTerminalOnExit(int signal);

int main()
{
    bool finished = true, running = true;
    char picture[HEIGHT][WIDTH];
    std::string keyboardInput;
    int inputLength;
    
    // fix terminal on keyboard interupt
    std::signal(SIGINT, fixTerminalOnExit);

    // initiate paddles and picture
    Paddle leftPaddle(Point(0, 4)), rightPaddle(Point(19, 4));
    update(picture, true);

    // game loop
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // user input
        if (finished)
        {
            std::thread userInput(listen, std::ref(finished), std::ref(keyboardInput), std::ref(inputLength));

            handleUserInput(keyboardInput, inputLength, leftPaddle, rightPaddle);

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

void listen(bool& finished, std::string& keyboardInput, int& length)
{
    // read keyboard input \\
    finished = true;
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
            case 'u' :
                rightPaddle.velocity.y = 1;
                break;
            case 'd' :
                rightPaddle.velocity.y = -1;
                break;
        }
    }
}

void fixTerminalOnExit(int signal)
{
    std::cout << "Program exiting! :)" << std::endl;
    system("stty cooked");
    exit(0);
}