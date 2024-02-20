#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define error return 0
// Set the LCD address to 0x27 for a 16 chars and 2 line display
#include "mastermind.h"
#include "lcd_wrapper.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // initialize the LCD
  lcd.init();
  lcd.backlight();
    // 1. blue
  pinMode(6, OUTPUT);
  // 1. red
  pinMode(7, OUTPUT);
  // 2. blue
  pinMode(8, OUTPUT);
  // 2. red
  pinMode(9, OUTPUT);
  // 3. blue
  pinMode(10, OUTPUT);
  // 3. red
  pinMode(11, OUTPUT);
  // 4. blue
  pinMode(12, OUTPUT);
  // 4. red
  pinMode(13, OUTPUT);
  
  // button 1
  pinMode(A0, INPUT);
  // button 2
  pinMode(2, INPUT);
  // button 3
  pinMode(3, INPUT);
  // button 4
  pinMode(4, INPUT);
  // enter
  pinMode(5, INPUT);
 
}

void loop(){
    char* code = generate_code(true, 4);
    play_game(code);
    free(code);
}
