#include <Arduino.h>
#include "bot.h"
#include "countdown.h"
#include "webserver.h"
#include "wifiCred.h"

void countdownTask(void* paramater);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  setupBot();
  setupWebServer();
  xTaskCreatePinnedToCore(countdownTask, "CountdownTask", 4096, NULL, 1, NULL, 0);
}

void loop() {
    serverHandleClient();
    comunicateToBot();
}


void countdownTask(void* paramater) {
    while(true) {
        handleCountdownTick();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}