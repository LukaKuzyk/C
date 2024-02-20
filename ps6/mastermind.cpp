#include <stdio.h>
#include "mastermind.h"
#include <stdlib.h>
#include <stdbool.h>

char* generate_code(bool repeat, int length){
  if((length > 10 && repeat == false)|| length < 1){
      fprintf(stderr, "Length is incorrect.\n");
      error;
  }
  char * output = (char*)calloc(1,length+1);
  int random_number = 0;
  if(repeat == true){
      for(short i=0; i<length; i++){
          random_number = rand() % 10;
          output[i] = random_number + 48;
      }
  }else{
    for(int i=0; i<length; i++){
        random_number = rand() % 10;
        random_number += 48;
        short index = 0;
        for(short a = 0; a<length;a++){
            if(output[a] != random_number){
                index++;
            }
        }
        if(index == length){
            output[i] = random_number;
        }else{
            i-=1;
        }
    }
  }
  return output;
}

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
    *peg_a = 0;
    *peg_b = 0;
    unsigned long length = strlen(secret);
    char * point = (char*)calloc(1, length + 1);
    strcpy(point, secret);
 
  for(int i=0; i<length; i++){
    if(point[i] == guess[i]){
        point[i] = 'A';
        *peg_a += 1;
    }
  }
  for(int i=0; i<length; i++){
    for(int a=0; a<length; a++){
      if(guess[i] == point[a]){
        *peg_b += 1;
        point[a] = 'B';
      }
    }
  }
    free(point);
}


void render_leds(const int peg_a, const int peg_b) {
  turn_off_leds();
  int a = peg_a;
  int b = peg_b;
  int position = 0;
  int pin;
  while (a != 0) {
    pin = position * 2;
    digitalWrite(7+pin, HIGH);
    digitalWrite(6+pin, 0);
    a--;
    position++;
  }
  while (b != 0) {
    pin = position * 2;
    digitalWrite(6+pin, HIGH);
    digitalWrite(7+pin, 0);
    b--;
    position++;
  }
}


void turn_off_leds() {
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  digitalWrite(9, 1);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
}


void print_text(const char * text){
  lcd.clear();
  lcd.print(text);
  delay(400);
  }

  void start_text(){
    lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
    delay(1000);
  lcd.print("MasterMind");
  lcd.setCursor(0,1);
  delay(2000);
  lcd.clear();
  char goal[] = "Your goal is to guess my secret combination.";
    lcd.setCursor(0,0);
    for(int i = 0; i<strlen(goal);i++){
      if(i==15){
       lcd.setCursor(0,1);
        }
        if(i==31){
          lcd.clear();
          lcd.setCursor(0,0);
        }
      lcd.write(goal[i]);
      delay(100);
      }
      
  delay(2000);

    }


void render_history(char* secret, char** history, const int entry) {
  int a,b;
  get_score(secret, history[entry], &a, &b);
  render_leds(a, b);
  lcd.clear();
  lcd.print(history[entry]);
}

void play_game(char* secret){
  turn_off_leds();
    start_text(); // HELLO atd
//  lcd.print(secret);
//  delay(500);
  print_text("Press any button");
  lcd.setCursor(0,1);
  delay(1000);
  lcd.print("to start game.");
  while(1){
    if(digitalRead(A0) == HIGH || digitalRead(2) == HIGH || digitalRead(3) == HIGH || digitalRead(4) == HIGH || digitalRead(5) == HIGH){
      break;
      }
//  digitalWrite(6, 1); //blue .  1 = blue; 0 = red
//  digitalWrite(7, 0); // red    0 = blue; 1 = red
//  digitalWrite(8, 1);
//  digitalWrite(9, 0);
//  digitalWrite(10, 1);
//  digitalWrite(11, 0);
//  digitalWrite(12, 1);
//  digitalWrite(13, 0);
    delay(100);
    }
  print_text("Lets start!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Your guess: 0000");


  int MAX_Tries = 10;
  int Current_Tries = 1;
  int a = 0, b = 0;
  int win = atoi(secret);
  char * score_guess = (char *) calloc(1, strlen(secret)+1);
  
  while(Current_Tries<=MAX_Tries){
    int guess = 0;
    int guess1 = 0;
    int guess2 = 0;
    int guess3 = 0;
    int guess4 = 0;

    delay(500);
    if(Current_Tries == 1){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Current Try: ");
    lcd.setCursor(13,1);
    lcd.print(Current_Tries);
    }else{
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(Current_Tries);

    lcd.setCursor(4,1);
    lcd.print("Prev.:");
    lcd.setCursor(11,1);
    lcd.print(score_guess);
    }

    while(digitalRead(5) != HIGH){ // ENTER
      if(digitalRead(A0) == HIGH){ // 1000
        guess1++;
        if(guess1 >9){
          guess1 = 0;
          }
        }

      if(digitalRead(2) == HIGH){ // 0100
        guess2++;
        if(guess2 >9){
          guess2 = 0;
          }
        }


      if(digitalRead(3) == HIGH){ // 0010
        guess3++;
        if(guess3 >9){
          guess3 = 0;
          }
        }

      if(digitalRead(4) == HIGH){ // 00010
        guess4++;
        if(guess4 >9){
          guess4 = 0;
          }
        }
        
        lcd.setCursor(0,0);
        lcd.print("Your guess:");
          lcd.setCursor(12,0);
          lcd.print(guess1);
          lcd.setCursor(13,0);
          lcd.print(guess2);
          lcd.setCursor(14,0);
          lcd.print(guess3);
          lcd.setCursor(15,0);
          lcd.print(guess4);

      delay(100);
      }
    guess += guess1*1000;
    guess += guess2*100;
    guess += guess3*10;
    guess += guess4;

    score_guess[0] = guess1 + 48;
    score_guess[1] = guess2 + 48;
    score_guess[2] = guess3 + 48;
    score_guess[3] = guess4 + 48;
//    lcd.clear();
//    lcd.print(score_guess);
//    delay(2000);

    get_score(secret, score_guess, &a, &b);
    render_leds(a,b);
    if(guess == win){
      lcd.clear();
      lcd.print("   YOU WIN!");
      delay(1000);
      lcd.clear();

      lcd.print("   YOU WIN!!");
      delay(1000);
            lcd.clear();

      lcd.print("   YOU WIN!!!");
      delay(7000);
      Current_Tries = -10;
      break;
      }

    Current_Tries++;
    }
    if(Current_Tries == MAX_Tries){
     lcd.clear();
     lcd.print("   YOU LOSE");
     delay(1000);
     lcd.setCursor(0,1);
     lcd.print("Number was:");
     lcd.setCursor(12,1);
     lcd.print(secret);
     delay(7000);
      }
     lcd.clear();
     lcd.print("Try again?? ");
     delay(1000);
     lcd.setCursor(0,1);
     lcd.print("Press any button");

  while(1){
    if(digitalRead(A0) == HIGH || digitalRead(2) == HIGH || digitalRead(3) == HIGH || digitalRead(4) == HIGH || digitalRead(5) == HIGH){
      break;
      }
    delay(100);
    }
     
  }
