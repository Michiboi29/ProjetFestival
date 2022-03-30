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
  // delay(500);
  // screen.blackScreen();
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

  // int max_val = 14;
  // for (int l = 0; l < max_val; l++){
  //   test_ligne(l);
  // }
  
  // test screen score

  // for (int j = 0; j < 10; j++){
  //   screen.displayScore(j, j);
  //   screen.refresh();
  //   delay(1000);
  // }
  
  // test game 

  if(game.run()){
    if(game.winner != 0){
      screen.gameOver(game.winner);
      game.winner = 0;
    }
    screen.startGame();
    game.restart = false;
  }
  else{
    screen.drawScreen(game.ball_x, game.ball_y, game.p1_y, game.p2_y, game.p1_score, game.p2_score);
  }
}