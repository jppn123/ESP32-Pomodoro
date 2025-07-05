#include <Arduino.h>
#include "util.h"
#include "logs.h"
#include "buzzer.h"

unsigned long previousMillis = 0;

uint32_t countdownSeconds = 1200;
bool isRunning = false;

void setCountdown(uint32_t seconds);
uint32_t getCountdown();
void pauseCountdown();
void startCountdown();

void startCountdown() {
    if (isRunning) return;
    isRunning = true;
    previousMillis = millis();
    addLog("Tempo iniciado em " + formatTimeMMSS(countdownSeconds));
}
  
void pauseCountdown() {
    if (!isRunning) return;
    isRunning = false;
    addLog("Tempo pausado em " + formatTimeMMSS(countdownSeconds));
}

void setCountdown(uint32_t seconds) {
    countdownSeconds = seconds;
    addLog("Tempo definido para " + formatTimeMMSS(countdownSeconds));
}

uint32_t getCountdown() {
    return countdownSeconds;
}

void adjustCountdown(int32_t secondsDelta) {
    int32_t newValue = (int32_t)countdownSeconds + secondsDelta;

    if (newValue < 0) {
        countdownSeconds = 0;
    } else {
        countdownSeconds = (uint32_t)newValue;
    }

    addLog("Tempo ajustado para " + formatTimeMMSS(countdownSeconds));
}

void handleCountdownTick() {
    if (isRunning) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= 1000) {
          previousMillis = currentMillis;
    
          if (countdownSeconds > 0) {
            countdownSeconds--;
            Serial.print("Tempo restante: ");
            Serial.println(formatTimeMMSS(countdownSeconds));
          } else {
            Serial.println("Tempo esgotado!");
            finishTime();
            isRunning = false;
          }
        }
    }
}