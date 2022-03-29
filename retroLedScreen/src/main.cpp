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
  for (int j = 0; j < 256; j++){
    CRGB color = CRGB(j,0,0);
    int max_val = 20;
    for (int x = 0; x < max_val; x++){
      screen.ledUpdate(x, ligne, color);
    }
    screen.refresh(); 
  }
  screen.blackScreen();
}

void setup() {  
  game.init();
  display.init();
  display.startGame();
  screen.init();
  sound.bounce();
  delay(500);
  sound.point();
}

void loop() {

  // test leds
  int max_val = 8;
  for (int l = 0; l < max_val; l++){
    test_ligne(l);
  }
  
  

  // test game serial

  // if(game.run()){
  //   if(game.winner != 0){
  //     display.gameOver(game.winner);
  //     game.winner = 0;
  //   }
  //   display.startGame();
  //   game.restart = false;
  // }
  // else{
  //   display.drawScreen(game.ball_x, game.ball_y, game.p1_y, game.p2_y, game.p1_score, game.p2_score);
  // }
}