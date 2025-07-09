#ifndef BOT_H
#define BOT_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOT_TOKEN "8085947503:AAE2skofcIwIkXRZJyxXs8aXbOBEe6LHgno"
#define CHAT_ID "1546484802"
#define DELAY 500
#endif

void setupBot();
void comunicateToBot();
void handleNewMessages(int numNewMessages);

