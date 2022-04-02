#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <ncurses.h>
#include "paddle.h"
#include "ball.h"
#include "point.h"

void update(char picture[HEIGHT][WIDTH], Paddle& left, Paddle& right, Ball& ball);
void draw(char picture[HEIGHT][WIDTH], WINDOW* gameWindow, int frame, int leftScore, int rightScore);
void listen(std::string& keyboardInput, WINDOW* gameWindow);
void handleUserInput(const std::string& inputs, int& length, Paddle& left, Paddle& right);
WINDOW* createGameWindow(int height, int width);

int main()
{
    bool running = true;
    std::string keyboardInput = "////";
    WINDOW* gameWindow;
    int inputLength, framePassed = 0, leftScore = 0, rightScore = 0;
    char picture[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            picture[i][j] = ' ';
    }

    // initiate paddles
    Paddle leftPaddle(Point(0, 4)), rightPaddle(Point(19, 4));

    // game window and text window
    initscr();
    noecho();
    gameWindow = createGameWindow(HEIGHT, WIDTH);
    noecho();
    keypad(stdscr, true);

    std::thread userInput(listen, std::ref(keyboardInput), std::ref(gameWindow));

    // game loop
    while (running)
    {
        framePassed++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        handleUserInput(keyboardInput, inputLength, leftPaddle, rightPaddle);
        draw(picture, gameWindow, framePassed, leftScore, rightScore);

    }

}

void update(char picture[HEIGHT][WIDTH], Paddle& left, Paddle& right, Ball& ball)
{
    

}


void draw(char picture[HEIGHT][WIDTH], WINDOW* gameWindow, int frame, int leftScore, int rightScore)
{
    // draw game window
    clear();
    wborder(gameWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(gameWindow, 0, 0);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            waddch(gameWindow, picture[i][j]);
        wmove(gameWindow, i + 1, 0);
    }

    // draw text
    mvwprintw(gameWindow, HEIGHT -1, 0, "Frames ellapsed: %i -- %i | %i --", frame, leftScore, rightScore);

    wrefresh(gameWindow);
}

void listen(std::string& keyboardInput, WINDOW* gameWindow)
{
    for (int i = 0; true; i++)
    {
        if (i == 4)
        {
            i = 0;
            keyboardInput = "////";
        }
        keyboardInput[i] = wgetch(gameWindow);
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
            case KEY_UP : // fill with up arrow key
                rightPaddle.velocity.y = 1;
                break;
            case KEY_DOWN : // fill with down arrow key
                rightPaddle.velocity.y = -1;
        }
    }
}

WINDOW* createGameWindow(int height, int width)
{
    WINDOW* localWin = newwin(height + 4, width + 2, 0, 0);

    // create border
    wborder(localWin, 0, 0, 0, 0, 0, 0, 0, 0);

    wrefresh(localWin);

    return localWin;
}