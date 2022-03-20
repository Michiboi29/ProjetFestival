
#include <SPI.h>
#include <Wire.h>

#define RESTART 6
#define P1_UP 2
#define P1_DOWN 3
#define P2_UP 4
#define P2_DOWN 5
const unsigned long PADDLE_RATE = 1;
const unsigned long BALL_RATE = 1;
const uint8_t PADDLE_HEIGHT = 4;
int P1_SCORE = 0;
int P2_SCORE = 0;
int MAX_SCORE = 8;
bool resetBall = false;
#define SCREEN_HEIGHT = 14;
#define SCREEN_WIDTH = 20;

uint8_t ball_x = 10, ball_y = 7;
uint8_t ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update;

unsigned long paddle_update;
// ou la paddle du p1 est
const uint8_t P1_X = 1;
uint8_t P1_y = 5;
// ou la paddle du p2 est
const uint8_t P2_x = 18;
uint8_t P2_y = 5;

void setup(){
    unsigned long start = millis();
    // Button du P1 
    pinMode(P1_UP, INPUT);
    pinMode(P1_DOWN, INPUT);
    // Chngement detat si le button est press P1
    digitalWrite(P1_UP, 1);
    digitalWrite(P1_DOWN, 1);

    // Button du P2
    pinMode(P2_UP, INPUT);
    pinMode(P2_DOWN, INPUT);
    // Chngement detat si le button est press P2
    digitalWrite(P2_UP, 1);
    digitalWrite(P2_DOWN, 1);

    // Reset de la Partie
    pinMode(RESTART, INPUT_PULLUP);

    display.display();

    ball_update = millis();
    paddle_update = ball_update;

}


void loop() {
    bool update = false;
    unsigned long time = millis();



}