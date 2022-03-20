#include <Arduino.h>

int player1_val;
int player2_val;
const int player1_pot = A0;
const int player2_pot = A1;

void setup() {
  pinMode(player1_pot, INPUT);
  pinMode(player2_pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  player1_val = analogRead(player1_pot);
  player2_val = analogRead(player2_pot);
  Serial.print(millis());
  Serial.print(" ");
  Serial.print(player1_val);
  Serial.print(" ");
  Serial.println(player2_val);
  
}