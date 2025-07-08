#include <Arduino.h>

enum EstadoSistema {
    PARADO,
    RODANDO,
    PAUSADO,
    REINICIADO
};

extern EstadoSistema estadoSistema;

String formatTimeMMSS(int totalSeconds);
int parseTimeMMSS(const String& timeStr);