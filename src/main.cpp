#include <Arduino.h>
#include "bot.h"


void setup() {
    Serial.begin(115200);
    
    setupBot();
}

void loop() {
    comunicateToBot();
}