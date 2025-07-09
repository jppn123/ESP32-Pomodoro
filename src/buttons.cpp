#include <Arduino.h>
#include "buttons.h"
#include "util.h"
#include "countdown.h"

unsigned long buttonPressTime1 = 0;
unsigned long buttonPressTime2 = 0;
unsigned long buttonPressTime3 = 0;
bool button3Held = false;
bool buttonHandled = false; 
bool actionDone1 = false;
bool actionDone2 = false;

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
    if (buttonPressTime1 == 0) {
      buttonPressTime1 = millis();
    }

    if (!actionDone1) {
      if (button3Held) {
        if ((millis() - buttonPressTime1) < 400) {
          adjustCountdown((5 * 60));
          Serial.println("Botão 1: ajuste de tempo");
          actionDone1 = true;
        }
      } else {
        
        startCountdown();
        Serial.println("Botão 1: iniciar");
        actionDone1 = true;
      }
    }
  } else {
    buttonPressTime1 = 0;
    actionDone1 = false;
  }

  if (buttonState2 == LOW) {
    if (buttonPressTime2 == 0) {
      buttonPressTime2 = millis();
    }

    if (!actionDone2) {
      if (button3Held) {
        if ((millis() - buttonPressTime2) < 400) {
          adjustCountdown(-(5 * 60));
          Serial.println("Botão 2: ajuste de tempo");
          actionDone2 = true;
        }
      } else {
        pauseCountdown();
        Serial.println("Botão 2: pausar");
        actionDone2 = true;
      }
    }
  } else {
    buttonPressTime2 = 0;
    actionDone2 = false;
  }

  if (buttonState3 == LOW) {
    if (buttonPressTime3 == 0) {
      buttonPressTime3 = millis();
    }
  } else {
    // Botão foi solto
    if (buttonPressTime3 > 0 && !buttonHandled) {
      unsigned long pressDuration = millis() - buttonPressTime3;

      if (pressDuration < 500) {
        if(button3Held){
          state = "updated";
          button3Held = false;
        }else{
          setCountdown(20 * 60);
          pauseCountdown();
          state = "restarted";
        }

      } else {
        button3Held = true;
        setCountdown(20 * 60);
        pauseCountdown();
        state = "updating";
      }

      buttonHandled = true;
    }
    buttonPressTime3 = 0;
  } 
  if (buttonState3 == HIGH && buttonHandled) {
    buttonHandled = false;
  }
  
  delay(50);
}