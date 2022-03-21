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
  display.drawScreen(game.ball_x, game.ball_y, game.p1_y, game.p2_y, game.p1_score, game.p2_score);
}