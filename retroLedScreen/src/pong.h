#ifndef PONG_H
#define PONG_H

#include "Arduino.h"

// PINS
#define RESTART 6
#define P1_UP 2
#define P1_DOWN 3
#define P2_UP 4
#define P2_DOWN 5

// Constants
#define PADDLE_HEIGHT 4
#define SCREEN_HEIGHT 14
#define SCREEN_WIDTH 20
#define MAX_SCORE 8

class Pong{
    public:
        void init();
        void run();
        void gameOver();

        bool update = false;
        int p1_score = 0;
        int p2_score = 0;
        int ball_x = 10, ball_y = 7;
        int ball_dir_x = 1, ball_dir_y = 1;
        int p1_y = 5;
        int p2_y = 5;

    private:
        void gameReset();
        void resetBall();
        void paddleStateUpdate();
        void updateBall();
        void updatePaddle();

        const int p1_x = 1;
        const int p2_x = 18;
        const int paddle_rate = 1;
        int ball_rate = 1;
        bool reset_ball = false;
        unsigned long ball_update;
        unsigned long paddle_update;
        unsigned long start;
        bool p1_up_state = false;
        bool p1_down_state = false;
        bool p2_up_state = false;
        bool p2_down_state = false;
};

#endif //PONG_H