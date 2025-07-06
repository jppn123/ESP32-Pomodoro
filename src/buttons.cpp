#include <Arduino.h>
#include "buttons.h"
#include "util.h"
#include "countdown.h"

void setupButtons() {
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
}

void useButtons() {
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  int buttonState3 = digitalRead(BUTTON_PIN3);

  if (buttonState1 == LOW) {
    startCountdown();
    Serial.println("Botão pressionado 1 pressionado");
  }
  if (buttonState2 == LOW ) {
    pauseCountdown();
    Serial.println("Botão pressionado 2 pressionado");
  }
  if(buttonState3 == LOW){
    
    Serial.println("Botão pressionado 3 pressionado");
  }

  delay(50);
}