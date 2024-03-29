#include "ball.h"
#include "paddle.h"
#include "point.h"
#include <chrono>
#include <ncurses.h>
#include <string>
#include <thread>

void update(chtype picture[HEIGHT][WIDTH], Paddle &left, Paddle &right,
            Ball &ball, int &leftScore, int &rightScore, whoWon &result);
void draw(chtype picture[HEIGHT][WIDTH], WINDOW *gameWindow, int leftScore,
          int rightScore);
void blankScreen(chtype picture[HEIGHT][WIDTH], Paddle &left, Paddle &right,
                 Ball &ball);
void listen(std::string &keyboardInput, WINDOW *gameWindow, int &length,
            bool &running);
void handleUserInput(std::string inputs, int &length, Paddle &left,
                     Paddle &right);
WINDOW *createGameWindow(int height, int width);

int main() {
    bool running = true;
    char keyboardInput[100] = {0};
    WINDOW *gameWindow;
    whoWon frameResult;
    int inputLength = 4, framePassed = 0, leftScore = 0, rightScore = 0;
    chtype picture[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            picture[i][j] = ' ';
    }

    // instantiate game objects
    Paddle leftPaddle(Point(0, HEIGHT / 2)),
        rightPaddle(Point(WIDTH - 1, HEIGHT / 2));
    Point pos((int)(WIDTH / 2), (int)(HEIGHT / 2)), vel(1, -1);
    Ball ball(pos, vel);

    // game window and text window
    initscr();
    gameWindow = createGameWindow(HEIGHT, WIDTH);
    noecho();
    keypad(gameWindow, true);

    std::thread userInput(listen, std::ref(keyboardInput), std::ref(gameWindow),
                          std::ref(inputLength), std::ref(running));

    // game loop
    while (running) {
        framePassed++;
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));

        blankScreen(picture, leftPaddle, rightPaddle, ball);
        handleUserInput(keyboardInput, inputLength, leftPaddle, rightPaddle);
        memset(keyboardInput, 0, sizeof(keyboardInput));
        update(picture, leftPaddle, rightPaddle, ball, leftScore, rightScore,
               frameResult);
        if (frameResult)
            running = false;
        draw(picture, gameWindow, leftScore, rightScore);
    }

    mvwprintw(gameWindow, HEIGHT + 2, (WIDTH / 2) + 8,
              "Press any key to end game.");
    wrefresh(gameWindow);

    // close game
    userInput.join();
    endwin();
    if (frameResult == rightWin)
        printf("Right side won!! Score was: %i | %i\n", leftScore, rightScore);
    else
        printf("Left side won!! Score was: %i | %i\n", leftScore, rightScore);
}

void blankScreen(chtype picture[HEIGHT][WIDTH], Paddle &left, Paddle &right,
                 Ball &ball) {
    // left paddle
    picture[left.location.y][left.location.x] = ' ';
    picture[left.location.y + 1][left.location.x] = ' ';
    picture[left.location.y + 2][left.location.x] = ' ';

    // right paddle
    picture[right.location.y][right.location.x] = ' ';
    picture[right.location.y + 1][right.location.x] = ' ';
    picture[right.location.y + 2][right.location.x] = ' ';

    // ball
    picture[ball.location.y][ball.location.x] = ' ';
}

void update(chtype picture[HEIGHT][WIDTH], Paddle &left, Paddle &right,
            Ball &ball, int &leftScore, int &rightScore, whoWon &result) {
    left.move();
    right.move();
    result = ball.collision(left, right, leftScore, rightScore);
    ball.move();

    // left paddle
    picture[left.location.y][left.location.x] = '!';
    picture[left.location.y + 1][left.location.x] = '!';
    picture[left.location.y + 2][left.location.x] = '!';

    // right paddle
    picture[right.location.y][right.location.x] = '!';
    picture[right.location.y + 1][right.location.x] = '!';
    picture[right.location.y + 2][right.location.x] = '!';

    // ball
    picture[ball.location.y][ball.location.x] = ACS_DIAMOND;
}

void draw(chtype picture[HEIGHT][WIDTH], WINDOW *gameWindow, int leftScore,
          int rightScore) {
    // draw game window
    clear();

    // top line of border
    mvwaddch(gameWindow, 0, 0, ACS_ULCORNER);
    for (int i = 0; i < WIDTH; i++)
        waddch(gameWindow, ACS_HLINE);
    waddch(gameWindow, ACS_URCORNER);

    // print picture
    wmove(gameWindow, 1, 0);
    for (int i = 0; i < HEIGHT; i++) {
        waddch(gameWindow, ACS_VLINE);
        for (int j = 0; j < WIDTH; j++)
            waddch(gameWindow, picture[i][j]);
        waddch(gameWindow, ACS_VLINE);
        wmove(gameWindow, i + 2, 0);
    }

    // draw bottom border
    waddch(gameWindow, ACS_LLCORNER);
    for (int i = 0; i < WIDTH; i++)
        waddch(gameWindow, ACS_HLINE);
    waddch(gameWindow, ACS_LRCORNER);

    // draw text
    mvwprintw(gameWindow, HEIGHT + 2, (WIDTH / 2) - 7, "-- %i | %i --",
              leftScore, rightScore);

    wrefresh(gameWindow);
}

void listen(std::string &keyboardInput, WINDOW *gameWindow, int &length,
            bool &running) {
    int newChar;
    for (int i = 0; running; i++) {
        if (i == 4) {
            i = 0;
            length = 0;
        }
        newChar = wgetch(gameWindow);
        if (newChar == KEY_UP)
            newChar = FAKEUP;
        if (newChar == KEY_DOWN) // issues
            newChar = FAKEDOWN;
        keyboardInput[i] = newChar;
        length++;
    }
}

void handleUserInput(std::string inputs, int &length, Paddle &leftPaddle,
                     Paddle &rightPaddle) {
    bool leftPressed = false, rightPressed = false;
    // modify the velocities of paddles
    for (int i = 0; i < length; i++) {
        switch (inputs[i]) {
        case 'w':
            leftPaddle.velocity.y = -1;
            leftPressed = true;
            break;
        case 's':
            leftPaddle.velocity.y = 1;
            leftPressed = true;
            break;
        case FAKEUP: // fill with up arrow key
            rightPaddle.velocity.y = -1;
            rightPressed = true;
            break;
        case FAKEDOWN: // fill with down arrow key
            rightPaddle.velocity.y = 1;
            rightPressed = true;
        }
    }
    if (!leftPressed)
        leftPaddle.velocity = Point(0, 0);
    if (!rightPressed)
        rightPaddle.velocity = Point(0, 0);
}

WINDOW *createGameWindow(int height, int width) {
    WINDOW *localWin = newwin(height + 4, width + 2, 0, 0);

    wrefresh(localWin);

    return localWin;
}
