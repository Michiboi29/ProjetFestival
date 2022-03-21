#include "pong.h"

void Pong::init(){
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

    gameReset();
}


void Pong::runGame() {
    unsigned long time = millis();

    // read reset button
    if(digitalRead(RESTART) == LOW){
        gameReset();
    }

    if(reset_ball)
    {
        resetBall();
    }

    paddleStateUpdate();

    if(time > ball_update){
        updateBall();
    }
    if(time > paddle_update) {
        updatePaddle();
    }
}

void Pong::resetBall(){
    if(p1_score == MAX_SCORE || p2_score == MAX_SCORE)
    {
        gameOver();
    }
    else{
        ball_x = random(9, 10);
        ball_y = random(5, 8);
            do{
                ball_dir_x = random(-1,1);
            }while(ball_dir_x == 0);
            do
            {
                ball_dir_y = random(-1,1);
            }while(ball_dir_y == 0);
        reset_ball = false;
    }
}

void Pong::paddleStateUpdate(){
    p1_up_state |= (digitalRead(P1_UP) == LOW);
    p1_down_state |= (digitalRead(P1_DOWN) == LOW);
    p2_up_state |= (digitalRead(P2_UP) == LOW);
    p2_down_state |= (digitalRead(P2_DOWN) == LOW);
}

void Pong::gameReset(){
    start = millis();
    while (millis() - start < 2000);
    ball_update = millis();
    paddle_update = ball_update;
    reset_ball = true;
}

void Pong::gameOver(){
    gameReset();
}

void Pong::updateBall(){
    int new_x = ball_x + ball_dir_x;
    int new_y = ball_y + ball_dir_y;
    // Verifier si on touche un  mur
    if( new_x == 0 || new_x == 19){
        // Si P2 a scorrer
        if(new_x == 0){
            p1_score++;
            reset_ball = true;
        }
        // Si p1 a scorrer
        else if(new_y == 19){
            p2_score++;
            reset_ball = true;
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
    if ( (new_x == p1_x && new_y >= p1_y) && new_y <= (p1_y + PADDLE_HEIGHT)){
        ball_dir_x = -ball_dir_x; // changement de la direction
        new_x += ball_dir_x + ball_dir_x; // nouvelle pos
    }
    // verifier si on touche la paddle p2
    if ((new_x == p2_x && new_y >= p2_y ) && new_y <= (p2_y + PADDLE_HEIGHT)){
        ball_dir_x = -ball_dir_x; // changement de la direction
        new_x += ball_dir_x + ball_dir_x; // nouvelle pos
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
        p1_y++;
    }
    if(p1_down_state){
        p1_y--;
    }
    if(p1_y < 0){
        p1_y = 0;
    }
    if((p1_y + PADDLE_HEIGHT) > 13){
        p1_y = 13 - PADDLE_HEIGHT;
    }
    p1_down_state = p1_up_state = false;
    // P2
    if(p2_up_state){
        p2_y++;
    }
    if(p2_down_state){
        p2_y--;
    }
    if(p2_y < 0){
        p2_y = 0;
    }
    if((p2_y + PADDLE_HEIGHT) > 13){
        p2_y = 13 - PADDLE_HEIGHT;
    }
    p2_down_state = p2_up_state = false;
    
    update = true;
}