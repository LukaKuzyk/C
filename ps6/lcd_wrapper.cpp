#include <Arduino.h>

#include "lcd_wrapper.h"


void lcd_init(){
}

void lcd_clear(){
}


void lcd_set_cursor(int y, int x){
    lcd.setCursor(y,x);
}


void lcd_print(char* text){
   lcd.print(text);
}


void lcd_print_at(int y, int x, char* text){
   lcd_set_cursor(y, x);
   lcd_print(text);
}

