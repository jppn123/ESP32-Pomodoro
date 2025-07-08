#include <Arduino.h>
#include "lcd.h"
#include "countdown.h"
#include "util.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void startLCD() {
  lcd.setCursor(0, 0); 
  lcd.print("Pomodoro ESP32");
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

  if (tempo != ultimoTempo) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(tempo);
    ultimoTempo = tempo;
  }
}
