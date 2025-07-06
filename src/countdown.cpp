#include <Arduino.h>
#include "util.h"
#include "logs.h"
#include "buzzer.h"
#include "countdown.h"

unsigned long previousMillis = 0;

uint32_t countdownSeconds = 1200;
uint32_t settedCountdownSeconds = 0;
bool isRunning = false;
String state = "paused";

void startCountdown() {
    if (isRunning || countdownSeconds == 0) return;
    isRunning = true;
    state = "started";
    previousMillis = millis();
    addLog("Tempo iniciado em " + formatTimeMMSS(countdownSeconds));
}
  
void pauseCountdown() {
    if (!isRunning) return;
    isRunning = false;
    state = "paused";
    addLog("Tempo pausado em " + formatTimeMMSS(countdownSeconds));
}

void setCountdown(uint32_t seconds) {
    if(settedCountdownSeconds != 0) {
        seconds = settedCountdownSeconds;
    }
    countdownSeconds = seconds;
    addLog("Tempo definido para " + formatTimeMMSS(countdownSeconds));
}

void newCountdown(uint32_t seconds) {
    settedCountdownSeconds = seconds;
    addLog("Novo tempo definido para " + formatTimeMMSS(countdownSeconds));
}

uint32_t getCountdown() {
    return countdownSeconds;
}

void adjustCountdown(int32_t secondsDelta) {
    int32_t newValue = (int32_t)countdownSeconds + secondsDelta;

    if (newValue < 0) {
        countdownSeconds = 0;
    }
    else if(newValue > 3600){
        countdownSeconds = 3600;
    } 
    else {
        countdownSeconds = (uint32_t)newValue;
    }
    newCountdown(countdownSeconds);
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