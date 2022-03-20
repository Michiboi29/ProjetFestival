
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

    static bool P1_up_state = false;
    static bool P1_down_state = false;
    static bool P2_up_state = false;
    static bool P2_down_state = false;

    if(digitalRead(RESTART)== LOW){
        gameOver();
    }
    if(resetBall)
    {
        if(P1_SCORE == maxScore || P2_SCORE == MAX_SCORE)
        {
            gameOver();
        }
    else{
        ball_x = random(9,10);
        ball_y = random(5, 8);
        do{
            ball_dir_x = random(-1,1);
    }while(ball_dir_x == 0);
    do
    {
        ball_dir_y = random(-1,1);
    }while(ball_dir_y == 0);
        resetBall = false;
        }
    }

    P1_up_state |= (digitalRead(P1_UP)== LOW);
    P1_down_state |= (digitalRead(P1_DOWN)== LOW);
    P2_up_state |= (digitalRead(P2_UP)== LOW);
    P2_down_state |= (digitalRead(P2_DOWN)== LOW);

    if(time > ball_update){
        uint8_t new_x = ball_x + ball_dir_x;
        uint8_t new_y = ball_y + ball_dir_y;
        // Verifier si on touche un  mur
        if( new_x == 0 || new_x == 19){
            // Si P2 a scorrer
            if(new_x == 0){
                P1_SCORE++;
                resetBall = true;
            }
            // Si p1 a scorrer
            else if(new_y == 19){
                P2_SCORE++;
                resetBall =true;
            }
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }
        // verifier si touche plafond/plancher
        if(new_y == 0 || new_y == 13){
            ball_dir_y = -ball_dir_y; // changement de la direction
            new_y += ball_dir_y + ball_dir_y; // faire bouger la balle lus loin que le mur
        }
        // verifier si on touche la Paddle du P1
        if ( new_x == P1_X && new_y >= P1_y && new_y <= P1_y + PADDLE_HEIGHT){
            ball_dir_x = -ball_dir_x; // changement de la direction
            new_x += ball_dir_x + ball_dir_x; // nouvelle pos
        }
        // verifier si on touche la paddle p2
        if ( new_x == P2_X && new_y >= P2_y && new_y <= P2_y + PADDLE_HEIGHT){
            ball_dir_x = -ball_dir_x; // changement de la direction
            new_x += ball_dir_x + ball_dir_x; // nouvelle pos
        }
        ball_x = new_x; // assignation de la new pos
        ball_y = new_y; // assignation de la new pos

        ball_update += BALL_RATE;

        update = true; //update de l'etat de la partie
    }
    if(time > paddle_update) {
        paddle_update += PADDLE_RATE;
        
    }


}