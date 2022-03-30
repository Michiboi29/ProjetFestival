#include "ledMonitorDisplay.h"

void LedMonitorDisplay::init(){
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    blackScreen();
}

void LedMonitorDisplay::refresh(){
    FastLED.show();
}

void LedMonitorDisplay::ledUpdate(int x, int y, CRGB color){
    int n;
    if(y%2 == 0){ // pair
        n = y*NUM_XLEDS + x;
    }
    else{ // impair
        n = y*NUM_XLEDS + ((NUM_XLEDS - 1) - x);
    }
    leds[n] = color;
}

bool LedMonitorDisplay::isPaddleHeight(int paddle, int y){
  if ((y <= (screenHeight - 1 - paddle)) && y >= (screenHeight - 1 - paddle - (PADDLE_HEIGHT-1))){
    return true;
  }
  else return false;
}

void LedMonitorDisplay::displayScore(int p1, int p2){
    showDigit(p1, 5, 8, COLOR_SCORE_P1);
    showDigit(p2, 12, 8, COLOR_SCORE_P2);
}

void LedMonitorDisplay::drawScreen(int bal_x, int bal_y, int paddle_p1, int paddle_p2, int score_p1, int score_p2){
    for(int y=0; y < screenHeight;y++){
        // Draw score
        displayScore(score_p1, score_p2);
        // actual game screen
        for(int x = 0; x < screenWidth; x++){
            if(x == p1_posx){ //Draw paddle p1
                if(isPaddleHeight(paddle_p1, y)) { // p1
                    ledUpdate(x, y, COLOR_P1);
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else if(x == p2_posx){ //Draw paddle p2
                if(isPaddleHeight(paddle_p2, y)) { // p1
                    ledUpdate(x, y, COLOR_P2);
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else if(x == bal_x){ //Draw bal
                if(y == (screenHeight - 1 - bal_y)) { // p1
                    ledUpdate(x, y, COLOR_BALL);
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else{// Draw void
                ledUpdate(x, y, COLOR_VOID);
            }
        }
    }
    refresh();
    delay(updateSpeed);
}

void LedMonitorDisplay::startGame(){
    delay(100);
    blackScreen();
    showRegie();
    delay(3000);
    blackScreen();
}

void LedMonitorDisplay::gameOver(int winner){
    delay(100);
    blackScreen();
    if(winner == 1){
        showBlue();
    }
    else if(winner == 2){
        showRed();
    }
    if (winner != 0){
        delay(3000);
        blackScreen();
        showWins();
        delay(3000);
        blackScreen();
    }
}

void LedMonitorDisplay::blackScreen(){
    for (int n = 0; n < NUM_LEDS; n++){
        leds[n] = COLOR_VOID;
    }
    refresh();
}

void LedMonitorDisplay::showRegie(){
    for(int y=0; y < screenHeight;y++){
        for(int x = 0; x < screenWidth; x++){
            if (x >= 1 && x <= 18){
                if(y == 2){ //Draw underline
                    ledUpdate(x, y, COLOR_REGIE);
                }
                else if(y == 4){ // line 1
                    if(x == 2 || x == 4 || x == 8 || x == 13 || x == 15){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_REGIE);
                    }
                }
                else if(y == 5){ // line 2
                    if(x == 2 || x == 4 || (x >= 6 && x <= 8) || x == 10 
                    || x == 11 || x == 13 || x == 15 || x >= 17){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_REGIE);
                    }
                }
                else if(y == 6){ // line 3
                    if(x == 3 || x == 4 || x == 7 || x == 8 || x == 10 
                    || x == 13 || x == 15 || x == 18){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_REGIE);
                    }
                }
                else if(y == 7){ // line 4
                    if(x == 2 || x == 4 || (x >= 6 && x <= 8) 
                    || (x >= 10 && x <= 13) || x == 15 || x >= 17){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_REGIE);
                    }
                }
                else if(y == 8){ // line 5
                    if(x == 4 || x == 8 || x == 13 || x == 15){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_REGIE);
                    }
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else{// Draw void
                ledUpdate(x, y, COLOR_VOID);
            }
        }
    }
    refresh();
}

// P1 is blue
void LedMonitorDisplay::showBlue(){
    for(int y=0; y < screenHeight;y++){
        for(int x = 0; x < screenWidth; x++){
            if (x >= 3 && x <= 16){
                if(y == 3){ //Draw underline
                    ledUpdate(x, y, COLOR_P1);
                }
                else if(y == 5){ // line 1
                    if(x == 6 || x == 9 || x == 13){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P1);
                    }
                }
                else if(y == 6){ // line 2
                    if(x == 4 || x == 6 || x == 8 || x == 9 || x == 11
                    || x == 13 || x >= 15){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P1);
                    }
                }
                else if(y == 7){ // line 3
                    if(x == 5 || x == 6 || x == 8 || x == 9 || x == 11
                    || x == 13 || x == 16){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P1);
                    }
                }
                else if(y == 8){ // line 4
                    if(x == 4 || x == 6 || x == 8 || x == 9 || x == 11
                    || x == 13 || x >= 15){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P1);
                    }
                }
                else if(y == 9){ // line 5
                    if(x == 5 || x == 6 || x == 8 || x == 9 || x == 11
                    || x == 13){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P1);
                    }
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else{// Draw void
                ledUpdate(x, y, COLOR_VOID);
            }
        }
    }
    refresh();
}

// P2 is red
void LedMonitorDisplay::showRed(){
    for(int y=0; y < screenHeight;y++){
        for(int x = 0; x < screenWidth; x++){
            if (x >= 4 && x <= 14){
                if(y == 3){ //Draw underline
                    ledUpdate(x, y, COLOR_P2);
                }
                else if(y == 5){ // line 1
                    if(x == 5 || x == 7 || x == 11 || x == 14){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P2);
                    }
                }
                else if(y == 6){ // line 2
                    if(x == 5 || x == 7 || (x >= 9 && x <= 11) || x == 13){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P2);
                    }
                }
                else if(y == 7){ // line 3
                    if(x == 6 || x == 7 || (x >= 10 && x <= 11) || x == 13){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P2);
                    }
                }
                else if(y == 8){ // line 4
                    if(x == 5 || x == 7 || (x >= 9 && x <= 11) || x == 13){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P2);
                    }
                }
                else if(y == 9){ // line 5
                    if(x == 7 || x == 11 || x == 14){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_P2);
                    }
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else{// Draw void
                ledUpdate(x, y, COLOR_VOID);
            }
        }
    }
    refresh();
}

void LedMonitorDisplay::showWins(){
    for(int y=0; y < screenHeight;y++){
        for(int x = 0; x < screenWidth; x++){
            if (x >= 2 && x <= 17){
                if(y == 2){ //Draw underline
                    ledUpdate(x, y, COLOR_WIN);
                }
                else if(y == 4){ // line 1
                    if(x == 2 || x == 4 || x == 6 || x == 7 || x == 9
                    || x == 11 || x == 12 || x == 14 || x == 17){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_WIN);
                    }
                }
                else if(y == 5){ // line 2
                    if(x == 3 || x == 5 || x == 7 || x == 9 || x == 11 
                    || x == 12 || x == 14 || x == 15 || x == 16){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_WIN);
                    }
                }
                else if(y == 6){ // line 3
                    if(x == 3 || x == 5 || x == 7 || x == 9 || x == 11 
                    || x == 14 || x == 15 || x == 17){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_WIN);
                    }
                }
                else if(y == 7){ // line 4
                    if(x == 3 || x == 5 || x == 7 || x == 9 || x == 12 
                    || x == 14 || x == 16 || x == 17){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_WIN);
                    }
                }
                else if(y == 8){ // line 5
                    if(x == 3 || x == 5 || x == 7 || x == 9 || x == 11 
                    || x == 12 || x == 14 || x == 15){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, COLOR_WIN);
                    }
                }
                else{// Draw void
                    ledUpdate(x, y, COLOR_VOID);
                }
            }
            else{// Draw void
                ledUpdate(x, y, COLOR_VOID);
            }
        }
    }
    refresh();
}

void LedMonitorDisplay::showDigit(int digit, int pos_x, int pos_y, CRGB color){
    int min_x = pos_x;
    int max_x = min_x + 2;
    int min_y = pos_y;
    int max_y = min_y + 4;
    for(int x = min_x; x < max_x + 1; x++){
        for(int y = min_y; y < max_y + 1; y++){
            switch (digit%10)
            {
            case 0:
                if(x == min_x){
                    ledUpdate(x, y, color);
                }
                else if (x == min_x + 1){
                    if((y == min_y) || (y == max_y)){
                        ledUpdate(x, y, color);
                    }
                    else{
                        ledUpdate(x, y, COLOR_VOID);
                    }
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;

            case 1:
                if(x == min_x){
                    ledUpdate(x, y, COLOR_VOID);
                }
                else if (x == min_x + 1){
                    ledUpdate(x, y, COLOR_VOID);
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;
            
            case 2:
                if(x == min_x){
                    if(y == min_y + 3){
                        ledUpdate(x, y,  COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == min_x + 1){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == max_x){
                    if(y == min_y + 1){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                break;
            
            case 3:
                if(x == min_x){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == min_x + 1){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;
            
            case 4:
                if(x == min_x){
                    if((y == min_y) || (y == min_y + 1)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == min_x + 1){
                    if(y == min_y + 2){
                        ledUpdate(x, y, color);
                    }
                    else{
                        ledUpdate(x, y, COLOR_VOID);
                    }
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;
            
            case 5:
                if(x == min_x){
                    if(y == min_y + 1){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == min_x + 1){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == max_x){
                    if(y == min_y + 3){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                break;
            
            case 6:
                if(x == min_x){
                    ledUpdate(x, y, color);
                }
                else if (x == min_x + 1){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == max_x){
                    if(y == min_y + 3){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                break;
            
            case 7:
                if(x == min_x){
                    if(y == max_y){
                        ledUpdate(x, y, color);
                    }
                    else{
                        ledUpdate(x, y, COLOR_VOID);
                    }
                }
                else if (x == min_x + 1){
                    if(y == max_y){
                        ledUpdate(x, y, color);
                    }
                    else{
                        ledUpdate(x, y, COLOR_VOID);
                    }
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;
            
            case 8:
                if(x == min_x){
                    ledUpdate(x, y, color);
                }
                else if (x == min_x + 1){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;
            
            case 9:
                if(x == min_x){
                    if(y == min_y + 1){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == min_x + 1){
                    if((y == min_y + 1) || (y == min_y + 3)){
                        ledUpdate(x, y, COLOR_VOID);
                    }
                    else{
                        ledUpdate(x, y, color);
                    }
                }
                else if (x == max_x){
                    ledUpdate(x, y, color);
                }
                break;
            
            default:
                ledUpdate(x, y, COLOR_VOID);
                break;
            }
        }       
    }
}