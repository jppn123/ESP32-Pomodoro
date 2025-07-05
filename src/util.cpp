#include <Arduino.h>

String formatTimeMMSS(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    return String(minutes) + "min" + String(seconds) + "seg";
}
