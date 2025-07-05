#include <Arduino.h>

String formatTimeMMSS(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    return String(minutes) + "min" + String(seconds) + "seg";
}

int parseTimeMMSS(const String& timeStr) {
    int minutes, seconds;
    int matched = sscanf(timeStr.c_str(), "%d:%d", &minutes, &seconds);
    if (matched != 2 || minutes < 0 || seconds < 0 || seconds >= 60) {
        return -1; // Formato inválido
    }
    return minutes * 60 + seconds;
}