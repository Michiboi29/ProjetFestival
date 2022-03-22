#ifndef LEDMONITORDISPLAY_H
#define LEDMONITORDISPLAY_H

#include <Arduino.h>
#include "pong.h"
#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    280
#define NUM_XLEDS   20
#define NUM_YLEDS   14

const CRGB COLOR_VOID = (0,0,0);
const CRGB COLOR_P1 = (0,0,255); // blue
const CRGB COLOR_P2 = (255,0,0); // red
const CRGB COLOR_BALL = (160,200,150); // 40mA
const CRGB COLOR_REGIE = (190,40,15); // 20mA
const CRGB COLOR_WIN = (70,105,80); // 20mA

class LedMonitorDisplay{
    public:
    void init();
    void displayScore(int p1, int p2);
    void drawScreen(int bal_x, int bal_y, int paddle_p1, int paddle_p2, int score_p1, int score_p2);
    void startGame();
    void gameOver(int winner);

    private:
    bool isPaddleHeight(int paddle, int y);
    void ledUpdate(int x, int y, CRGB color);
    void blackScreen();
    void showRegie();
    void showBlue();
    void showRed();
    void showWins();

    CRGB leds[NUM_LEDS];
    CRGB ledMatrix[NUM_YLEDS][NUM_XLEDS];

    // Game Settings
    const int screenHeight = SCREEN_HEIGHT;
    const int screenWidth = SCREEN_WIDTH;
    const int updateSpeed = 200;
    const int p1_posx = 1;
    const int p2_posx = 18;

};

#endif //LEDMONITORDISPLAY_H