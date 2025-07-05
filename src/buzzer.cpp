#include <Arduino.h>
#include "buzzer.h"

void beep(int freq, int duration) {
  ledcAttachPin(BUZZER_PIN, 0);
  ledcWriteTone(0, freq);
  delay(duration);
  ledcWriteTone(0, 0);
}

void finishTime() {
  beep(2000, 200);  
  delay(500);
  beep(2000, 200);  
  delay(500);
  beep(2000, 200);  
  delay(500);
  beep(1000, 500); 
}