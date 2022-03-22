#include "serialMonitorDisplay.h"

void SerialMonitorDisplay::init(){
    Serial.begin(115200);
}

bool SerialMonitorDisplay::isPaddleHeight(int paddle, int y){
  if ((y <= (screenHeight - 1 - paddle)) && y >= (screenHeight - 1 - paddle - (PADDLE_HEIGHT-1))){
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
  for(int y=0; y < screenHeight+1;y++){
    if(y==0){ // Draw statusbar
       displayData(bal_x, bal_y, paddle_p1, paddle_p2);
       displayScore(score_p1, score_p2);
       Serial.println("");
    }
    else if(y==1){ // Draw the roof
      for(int x=0; x < screenWidth; x++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else if(y==(screenHeight)){ // Draw the floor
      for(int x=0; x < screenWidth; x++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else { // actual led screen
      for(int x = 0; x < screenWidth; x++){
        if(x == 0 || x == screenWidth -1){ //Draw Edge
          Serial.print("#");
        }
        else if(x == p1_posx){ //Draw paddle p1
          if(isPaddleHeight(paddle_p1, y)) { // p1
            Serial.print("|");
          }
          else{// Draw void
            Serial.print(".");
          }
        }
        else if(x == p2_posx){ //Draw paddle p2
          if(isPaddleHeight(paddle_p2, y)) { // p1
            Serial.print("|");
          }
          else{// Draw void
            Serial.print(".");
          }
        }
        else if(x == bal_x + 1){ //Draw bal
          if(y == (screenHeight - 1 - bal_y)) { // p1
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

void SerialMonitorDisplay::startGame(){
    Serial.println("");
  for(int y=0; y < screenHeight+1;y++){
    if(y==0){ // Draw statusbar
       
       Serial.println("");
    }
    else if(y==1){ // Draw the roof
      for(int x=0; x < screenWidth; x++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else if(y==(screenHeight)){ // Draw the floor
      for(int x=0; x < screenWidth; x++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else if (y==(screenHeight - 10)){ // start
        const int start_lengt = 5;
        String start_string[start_lengt] = {"s", "t", "a", "r", "t"};
        for(int x = 0; x < screenWidth; x++){
            if(x == 0 || x == screenWidth -1){ //Draw Edge
            Serial.print("#");
            }
            else if(x >= 4 && x < 4 + start_lengt){ //Draw paddle p1
                Serial.print(start_string[x-4]);
            }
            else{// Draw void
            Serial.print(".");
            }
        }
        Serial.println("");
    }
    else { // actual led screen
      for(int x = 0; x < screenWidth; x++){
        if(x == 0 || x == screenWidth -1){ //Draw Edge
          Serial.print("#");
        }
        else{// Draw void
          Serial.print(".");
        }
      }
      Serial.println("");
    }
  }
  delay(3000);
}

void SerialMonitorDisplay::gameOver(int winner){
  Serial.println("");
  for(int y=0; y < screenHeight+1;y++){
    if(y==0){ // Draw statusbar
       
       Serial.println("");
    }
    else if(y==1){ // Draw the roof
      for(int x=0; x < screenWidth; x++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else if(y==(screenHeight)){ // Draw the floor
      for(int x=0; x < screenWidth; x++){
        Serial.print("-");
      }
      Serial.println("");
    }
    else if (y==(screenHeight - 10)){ // start
        const int win_lengt = 7;
        String win_string[win_lengt] = {"P", String(winner), ".", "w", "i", "n", "s"};
        for(int x = 0; x < screenWidth; x++){
            if(x == 0 || x == screenWidth -1){ //Draw Edge
            Serial.print("#");
            }
            else if(x >= 4 && x < 4 + win_lengt){ //Draw paddle p1
                Serial.print(win_string[x-4]);
            }
            else{// Draw void
            Serial.print(".");
            }
        }
        Serial.println("");
    }
    else { // actual led screen
      for(int x = 0; x < screenWidth; x++){
        if(x == 0 || x == screenWidth -1){ //Draw Edge
          Serial.print("#");
        }
        else{// Draw void
          Serial.print(".");
        }
      }
      Serial.println("");
    }
  }
  delay(5000);
    
}