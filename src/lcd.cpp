#include <Arduino.h>
#include "lcd.h"
#include "countdown.h"
#include "util.h"

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void startLCD() {
  lcd.setCursor(0, 0); 
  lcd.print("Pomodoro ESP32");
}

void setupLCD() {
  lcd.begin(16, 2); 
  lcd.clear();
  startLCD();
}

void updateLCD() {
  String tempo = formatTimeMMSS(getCountdown());
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(tempo);
}