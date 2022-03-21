#include "serialMonitorDisplay.h"

void SerialMonitorDisplay::init(){
    Serial.begin(115200);
}

bool SerialMonitorDisplay::isPaddleHeight(int paddle, int i){
  if ((i <= (screenHeight - 1 - paddle)) && i >= (screenHeight - 1 - paddle - PADDLE_HEIGHT)){
    return true;
  }
  else return false;
}

void SerialMonitorDisplay::displayScore(int p1, int p2){
    Serial.print("   !!! P1 : ");
    Serial.print(p1);
    Serial.print(" vs P2 : ");
    Serial.print(p2);
    Serial.print(" !!!   ");
}

void SerialMonitorDisplay::displayData(int bal_x, int bal_y, int paddle_p1, int paddle_p2){
    Serial.print("bal x : ");
    Serial.print(bal_x);
    Serial.print(" bal y : ");
    Serial.print(bal_y);
    Serial.print(" paddle p1 : ");
    Serial.print(paddle_p1);
    Serial.print(" paddle p2 : ");
    Serial.print(paddle_p2);
}

void SerialMonitorDisplay::drawScreen(int bal_x, int bal_y, int paddle_p1, int paddle_p2, int score_p1, int score_p2){
  Serial.println("");
  for(int i=0; i < screenHeight+1;i++){
    if(i==0){ // Draw statusbar
       displayData(bal_x, bal_y, paddle_p1, paddle_p2);
       displayScore(score_p1, score_p2);
       Serial.println("");
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
    else { // actual led screen
      for(int a = 0; a < screenWidth; a++){
        if(a == 0 || a == screenWidth -1){ //Draw Edge
          Serial.print("#");
        }
        else if(a == p1_posx){ //Draw paddle p1
          if(isPaddleHeight(paddle_p1, i)) { // p1
            Serial.print("|");
          }
          else{// Draw void
            Serial.print(".");
          }
        }
        else if(a == p2_posx){ //Draw paddle p2
          if(isPaddleHeight(paddle_p2, i)) { // p1
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