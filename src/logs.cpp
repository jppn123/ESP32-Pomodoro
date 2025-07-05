// logs.cpp

#include <LittleFS.h>
#include "logs.h"
#include <LittleFS.h>

#define FORMAT_LITTLEFS_IF_FAILED true
const char* LOGS_FILENAME = "/logs.txt";

bool addLog(String log) {
  if (log.isEmpty()) return false;
  File file = LittleFS.open(LOGS_FILENAME, FILE_APPEND);
  if (!file) {
    Serial.println("Erro ao abrir arquivo para log: " + String(LOGS_FILENAME));
    return false;
  }
  
  if (file.println(log)) {
    Serial.println("Log gravado: " + log);
  } else {
    Serial.println("Erro ao gravar log no arquivo: " + String(LOGS_FILENAME));
  }
  
  file.close();
  return true;
}

String readLastLogs(int quantity) {
  File file = LittleFS.open(LOGS_FILENAME, "r");
  if (!file || file.size() == 0) {
    return "Nenhum log encontrado.";
  }

  String* lines = new String[quantity];
  int lineCount = 0;
  String currentLine = "";
  long pos = file.size() - 1;

  while (pos >= 0 && lineCount < quantity) {
    file.seek(pos);
    char c = file.read();

    if (pos == file.size() - 1 && c == '\n') {
      pos--;
      continue;
    }

    if (c == '\n' || pos == 0) {
      if (pos == 0) currentLine = c + currentLine;
      lines[lineCount++] = currentLine;
      currentLine = "";
    } else {
      currentLine = c + currentLine;
    }
    pos--;
  }
  
  file.close();

  String result = "";
  for (int i = 0; i < lineCount; i++) {
    result += lines[i] + "\n";
  }

  delete[] lines;
  return result;
}

void initFS() {
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
      Serial.println("Erro ao montar LittleFS");
      return;
    }

    File file;
    if (!LittleFS.exists(LOGS_FILENAME)) {
      file = LittleFS.open(LOGS_FILENAME, FILE_WRITE);
      if (file) file.close();
    }
  }