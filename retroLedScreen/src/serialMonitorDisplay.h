#ifndef SERIALMONITORDISPLAY_H
#define SERIALMONITORDISPLAY_H

#include <Arduino.h>
#include "pong.h"


class SerialMonitorDisplay{
    public:
    void init();
    void displayScore(int p1, int p2);
    void displayData(int bal_x, int bal_y, int paddle_p1, int paddle_p2);
    void drawScreen(int bal_x, int bal_y, int paddle_p1, int paddle_p2, int score_p1, int score_p2);
    void startGame();
    void gameOver(int winner);


    private:
    bool isPaddleHeight(int paddle, int y);

    // Game Settings
    const int screenHeight = SCREEN_HEIGHT + 2;
    const int screenWidth = SCREEN_WIDTH + 2;
    const int updateSpeed = 200;
    const int p1_posx = 2;
    const int p2_posx = 19;

};

#endif //SERIALMONITORDISPLAY_H