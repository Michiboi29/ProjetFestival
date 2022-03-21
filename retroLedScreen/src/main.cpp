#include <Arduino.h>
#include "pong.h"
#include "serialMonitorDisplay.h"

Pong game;
SerialMonitorDisplay display;

void setup() {  
  game.init();
  display.init();
}

void loop() {
  game.run();
  
  if(game.winner != 0){
    display.gameOver(game.winner);
  }
  else if(game.restart){
    display.startGame();
  }
  else{
    display.drawScreen(game.ball_x, game.ball_y, game.p1_y, game.p2_y, game.p1_score, game.p2_score);
  }
}