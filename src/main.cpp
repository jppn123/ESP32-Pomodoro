#include <Arduino.h>
#include "bot.h"
#include "countdown.h"
#include "server.h"
#include "wifiCred.h"
#include "relay.h"
#include "lcd.h"
#include "buttons.h"

void countdownTask(void* paramater);
void lcdTask(void* parameter);
void buttonTask(void* parameter);

TaskHandle_t buttonTaskHandle = NULL;

void setup() {
    Serial.begin(115200);

    setupRelay();
    modifyRelay(false);
    delay(100);
    setupLCD();
    setupButtons();

    xTaskCreatePinnedToCore(countdownTask, "CountdownTask", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(lcdTask, "LCDTask", 4096, NULL, 1, NULL, 1); 
    xTaskCreatePinnedToCore(buttonTask, "ButtonTask", 4096, NULL, 1, &buttonTaskHandle, 0);

    setupWiFi();
    setupBot();
    setupWebServer();
    
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

void lcdTask(void* parameter) {
    while (true) {
        updateLCD();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}



void buttonTask(void* parameter) {
    while (true) {
        useButtons();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}