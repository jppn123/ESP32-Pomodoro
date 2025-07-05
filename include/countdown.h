#include <Arduino.h>

extern uint32_t countdownSeconds;
extern bool isRunning;

void setCountdown(uint32_t seconds);
uint32_t getCountdown();
void pauseCountdown();
void startCountdown();
void adjustCountdown(int32_t secondsDelta);
void handleCountdownTick();
