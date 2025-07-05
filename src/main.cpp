#include <Arduino.h>
#include "bot.h"
#include "countdown.h"

void countdownTask(void* paramater);

void setup() {
  Serial.begin(115200);

  setupBot();
  xTaskCreatePinnedToCore(countdownTask, "CountdownTask", 4096, NULL, 1, NULL, 0);
}

void loop() {
    comunicateToBot();
}


void countdownTask(void* paramater) {
    while(true) {
        handleCountdownTick();
        vTaskDelay(1000);
    }
}