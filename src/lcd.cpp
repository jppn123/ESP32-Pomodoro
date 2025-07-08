#include <Arduino.h>
#include "lcd.h"
#include "countdown.h"
#include "util.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void startLCD() {
  lcd.setCursor(0, 0); 
  lcd.print("Pomodoro - Focus");
}

void setupLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  startLCD();
}

String ultimoTempo = "";

void updateLCD() {
  String tempo = formatTimeMMSS(getCountdown());
  String title = String("Pomodoro - ") + (IS_FOCUS_TIME ? "Focus" : "Sleep");
  

  if (tempo != ultimoTempo) {
    lcd.setCursor(0, 0); 
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(title);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(tempo);
    ultimoTempo = tempo;
  }
}
