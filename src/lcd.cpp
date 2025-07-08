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
bool LAST_IS_FOCUS_TIME = IS_FOCUS_TIME;

void updateLCD() {
  String tempo = formatTimeMMSS(getCountdown());

  if (LAST_IS_FOCUS_TIME != IS_FOCUS_TIME) {
    String title = String("Pomodoro - ") + (IS_FOCUS_TIME ? "Focus" : "Sleep");
    lcd.setCursor(0, 0); 
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(title);
  }
  

  if (tempo != ultimoTempo) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(tempo);
    ultimoTempo = tempo;
  }
}
