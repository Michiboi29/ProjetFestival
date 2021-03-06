#include "pong.h"

Sound gameSound;

void Pong::init(){
    // Button du P1 
    pinMode(P1_UP, INPUT_PULLUP);
    pinMode(P1_DOWN, INPUT_PULLUP);
    // Chngement detat si le button est press P1
    digitalWrite(P1_UP, 1);
    digitalWrite(P1_DOWN, 1);

    // Button du P2
    pinMode(P2_UP, INPUT_PULLUP);
    pinMode(P2_DOWN, INPUT_PULLUP);
    // Chngement detat si le button est press P2
    digitalWrite(P2_UP, 1);
    digitalWrite(P2_DOWN, 1);

    // Reset de la Partie
    pinMode(RESTART, INPUT_PULLUP);

    gameReset();
}


int Pong::run() {
    unsigned long time = millis();

    // read reset button
    if(digitalRead(RESTART) == LOW){
        gameReset();
    }

    resetBall(reset_ball);

    if(restart){
        return 1;
    }

    paddleStateUpdate();

    if(time > ball_update){
        updateBall();
    }
    if(time > paddle_update) {
        updatePaddle();
    }

    return 0;
}

void Pong::resetBall(uint8_t p_reset_ball){
    if (p_reset_ball != 0){
        if(p1_score == MAX_SCORE)
        {
            winner = 1;
            gameOver();
        }
        else if(p2_score == MAX_SCORE)
        {
            winner = 2;
            gameOver();
        }
        else{
            switch (p_reset_ball)
            {
            case 1: //p1 start with ball
                ball_x = p1_x;
                ball_y = p1_y;
                ball_dir_x = 1;
                ball_dir_y = 1;
                break;
            case 2: // p2 start with ball
                ball_x = p2_x;
                ball_y = p2_y;
                ball_dir_x = -1;
                ball_dir_y = -1;
                break;
            case 3: // reset
                ball_x = random(9, 10);
                ball_y = random(5, 8);
                do{
                    ball_dir_x = random(-1,2);
                }while(ball_dir_x == 0);
                do
                {
                    ball_dir_y = random(-1,2);
                }while(ball_dir_y == 0);
                break;
            default: //reset
                ball_x = random(9, 10);
                ball_y = random(5, 8);
                do{
                    ball_dir_x = random(-1,2);
                }while(ball_dir_x == 0);
                do
                {
                    ball_dir_y = random(-1,2);
                }while(ball_dir_y == 0);
                break;
            }
            reset_ball = 0;
        }
    }
}

void Pong::paddleStateUpdate(){
    p1_up_state |= (digitalRead(P1_UP) == HIGH);
    p1_down_state |= (digitalRead(P1_DOWN) == HIGH);
    p2_up_state |= (digitalRead(P2_UP) == HIGH);
    p2_down_state |= (digitalRead(P2_DOWN) == HIGH);
}

void Pong::gameReset(){
    restart = true;
    p1_score = 0;
    p2_score = 0;
    start = millis();
    while (millis() - start < 1000);
    ball_update = millis();
    paddle_update = ball_update;
    reset_ball = 3;
}

void Pong::gameOver(){
    gameReset();
}

bool Pong::isPaddleP1Hit(int new_x, int new_y){
    if ((new_x == p1_x) && (new_y >= p1_y) && (new_y <= (p1_y + (PADDLE_HEIGHT - 1)))){
        return true;
    }
    return false;
}

bool Pong::isPaddleP2Hit(int new_x, int new_y){
    if ((new_x == p2_x) && (new_y >= p2_y ) && (new_y <= (p2_y + (PADDLE_HEIGHT - 1)))){
        return true;
    }
    return false;
}

void Pong::updateBall(){
    int new_x = ball_x + ball_dir_x;
    int new_y = ball_y + ball_dir_y;
    // Verifier si on touche un  mur
    if( new_x < 0 || new_x > (SCREEN_WIDTH - 1)){
        // Si P2 a scorrer
        if(new_x < 0){
            p2_score++;
            reset_ball = 1; // p1 lost
        }
        // Si p1 a scorrer
        else if(new_x > (SCREEN_WIDTH - 1)){
            p1_score++;
            reset_ball = 2; //p2 lost
        }
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
        gameSound.point();
    }
    // verifier si touche plafond/plancher
    if(new_y < 0 || new_y > (SCREEN_HEIGHT - 1)){
        ball_dir_y = -ball_dir_y; // changement de la direction
        new_y += ball_dir_y + ball_dir_y; // faire bouger la balle lus loin que le mur
        gameSound.bounce();
    }
    // verifier si on touche la Paddle du P1
    if (isPaddleP1Hit(new_x, new_y)){
        ball_dir_x = -ball_dir_x; // changement de la direction
        new_x += ball_dir_x + ball_dir_x; // nouvelle pos
        gameSound.bounce();
    }
    // verifier si on touche la paddle p2
    else if (isPaddleP2Hit(new_x, new_y)){
        ball_dir_x = -ball_dir_x; // changement de la direction
        new_x += ball_dir_x + ball_dir_x; // nouvelle pos
        gameSound.bounce();
    }
    ball_x = new_x; // assignation de la new pos
    ball_y = new_y; // assignation de la new pos

    ball_update += ball_rate;

    update = true; //update de l'etat de la partie
}

void Pong::updatePaddle(){
    paddle_update += paddle_rate;
    //P1
    if(p1_up_state){
        p1_y--;
    }
    if(p1_down_state){
        p1_y++;
    }
    if(p1_y < 0){
        p1_y = 0;
    }
    if((p1_y + (PADDLE_HEIGHT - 1)) >  (SCREEN_HEIGHT - 1)){
        p1_y = (SCREEN_HEIGHT - 1) - (PADDLE_HEIGHT-1);
    }
    p1_down_state = p1_up_state = false;
    // P2
    if(p2_up_state){
        p2_y--;
    }
    if(p2_down_state){
        p2_y++;
    }
    if(p2_y < 0){
        p2_y = 0;
    }
    if((p2_y + (PADDLE_HEIGHT - 1)) > (SCREEN_HEIGHT - 1)){
        p2_y = (SCREEN_HEIGHT - 1) - (PADDLE_HEIGHT-1);
    }
    p2_down_state = p2_up_state = false;
    
    update = true;
}


