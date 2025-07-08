#include <Arduino.h>

extern uint32_t countdownSeconds;
extern bool isRunning;
extern String state;
extern bool IS_FOCUS_TIME;

void setCountdown(uint32_t seconds);
uint32_t getCountdown();
void pauseCountdown();
void startCountdown();
void setCountdown(uint32_t seconds);
void newCountdown(uint32_t seconds);
void adjustCountdown(int32_t secondsDelta);
void handleCountdownTick();
