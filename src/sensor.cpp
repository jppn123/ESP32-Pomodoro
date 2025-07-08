#include <arduino.h>
#include "sensor.h"
#include "countdown.h"
#include "buzzer.h"

void ordenar(long arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        long temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

long medianaDuration() {
  const int n = 50;
  long leituras[n];

  for (int i = 0; i < n; i++) {
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);

    leituras[i] = pulseIn(ECHOPIN, HIGH);
    delay(5);
  }

  ordenar(leituras, n);
  return leituras[n / 2];
}

void setupSensor() {
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

void readSensor() {
  long duration = medianaDuration();
  float distanceCm = duration * SOUND_SPEED / 2;

  if(distanceCm > 100){
    pauseCountdown();
    beep(2000, 500);
  }


  Serial.print("duration (mediana): ");
  Serial.println(duration);
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
}