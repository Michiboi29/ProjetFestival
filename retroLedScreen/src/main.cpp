#include <Arduino.h>
#include "pong.h"
#include "serialMonitorDisplay.h"
#include "ledMonitorDisplay.h"
#include "sound.h"

Pong game;
SerialMonitorDisplay display;
LedMonitorDisplay screen;
Sound sound;

void test_ligne(int ligne){
  CRGB color = CRGB(180,0,0);
  int max_val = 20;
  for (int x = 0; x < max_val; x++){
    screen.ledUpdate(x, ligne, color);
  }
  screen.refresh();
}

void test_ecran(){
  int max_val = 14;
  for (int l = 0; l < max_val; l++){
    test_ligne(l);
  }
}


void setup() {  
  game.init();
  //display.init();
  //display.startGame();
  screen.init();
  sound.bounce();
  delay(200);
  sound.point();
}

void loop() {

  // test ecran rouge
  //test_ecran();
  
  // game pong ecran
  if(game.run()){
    if(game.winner != 0){
      // ecran
      screen.gameOver(game.winner);
      // serial
      //display.gameOver(game.winner);

      game.winner = 0;
    }
    // ecran
    screen.startGame();
    // serial
    //display.startGame();

    game.restart = false;
  }
  else{
    // ecran
    screen.drawScreen(game.ball_x, game.ball_y, game.p1_y, game.p2_y, game.p1_score, game.p2_score);
    // serial
    //display.drawScreen(game.ball_x, game.ball_y, game.p1_y, game.p2_y, game.p1_score, game.p2_score);
  }
}