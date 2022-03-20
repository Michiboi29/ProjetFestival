#include <Arduino.h>

// Game Settings
int screenHeight = 14 + 2;
int screenWidth = 20 + 2;
int updateSpeed = 1000;
int pad_h = 3;
int p1_posx = 2;
int p2_posx = 19;
bool isPaddleHeight(int padle, int i){
  if ((i <= (screenHeight - 1 - padle)) && i >= (screenHeight - 1 - padle - pad_h)){
    return true;
  }
  else return false;
}

void displayData(int bal_x, int bal_y, int padle_p1, int padle_p2){
  Serial.print("bal x :");
  Serial.print(bal_x);
  Serial.print(" bal y :");
  Serial.print(bal_y);
  Serial.print(" padle p1 :");
  Serial.print(padle_p1);
  Serial.print(" padle p2 :");
  Serial.println(padle_p2);
}
void drawScreen(int bal_x, int bal_y, int padle_p1, int padle_p2){
  Serial.println("");
  for(int i=0; i < screenHeight+1;i++){
    if(i==0){ // Draw statusbar
       displayData(bal_x, bal_y, padle_p1, padle_p2);
    }
    else if(i==1){ // Draw the roof
      for(int a=0; a < screenWidth; a++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else if(i==(screenHeight)){ // Draw the floor
      for(int a=0; a < screenWidth; a++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else { //actual led
      for(int a = 0; a < screenWidth; a++){
        if(a == 0 || a == screenWidth -1){ //Draw Edge
          Serial.print("#");
        }
        else if(a == p1_posx){ //Draw padle p1
          if(isPaddleHeight(padle_p1, i)) { // p1
            Serial.print("|");
          }
          else{// Draw void
            Serial.print(".");
          }
        }
        else if(a == p2_posx){ //Draw padle p2
          if(isPaddleHeight(padle_p2, i)) { // p1
            Serial.print("|");
          }
          else{// Draw void
            Serial.print(".");
          }
        }
        else if(a == bal_x + 1){ //Draw bal
          if(i == (screenHeight - 1 - bal_y)) { // p1
            Serial.print("*");
          }
          else{// Draw void
            Serial.print(".");
          }
        }
        else{// Draw void
          Serial.print(".");
        }
      }
      Serial.println("");
    }
  }
  delay(updateSpeed);
}

void setup() {  
  Serial.begin(115200);
}

void loop() {
  drawScreen(19,13,0,0);
}