#ifndef BOT_H
#define BOT_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOT_TOKEN "7344592024:AAGDK4Mu6kvV9U37gf_R8C8u32dgHDR5KEA"
#define CHAT_ID "7620344992"
#define DELAY 500
#endif

void setupBot();
void comunicateToBot();
void handleNewMessages(int numNewMessages);

