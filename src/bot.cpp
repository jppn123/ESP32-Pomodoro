#include <Arduino.h>
#include <vector>
#include "bot.h"
#include "wifiCred.h"
#include "countdown.h"
#include "WiFi.h"
#include "util.h"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long lastTimeBotRan;

void comunicateToBot();
void setupBot();
void handleNewMessages(int numNewMessages);


void handleNewMessages(int numNewMessages){
    for (int i=0; i<numNewMessages; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        if (chat_id != CHAT_ID){
            bot.sendMessage(chat_id, "Usuário não autorizado", "");
            continue;
        }
        
        String text = bot.messages[i].text;
        String from_name = bot.messages[i].from_name;

        if (text == "/start" || text == "/info") {
            String welcome = "Olá " + from_name + ",\n";
            welcome += "Use os comandos abaixo para controlar o sistema:\n\n";
            welcome += "/checar_tempo - Retorna o tempo setado no contador\n";
            welcome += "/iniciar_tempo - Inicia o tempo decrementando o contador\n";
            welcome += "/pausar_tempo - Pausa o contador\n";
            welcome += "/adicionar_tempo {tempo} - Adiciona um valor do contador no formato HH:MM:SS\n";
            welcome += "/diminuir_tempo {tempo} - Diminui um valor do contador no formato HH:MM:SS\n";
            welcome += "/definir_tempo {tempo} - Insere um valor para o contador no formato HH:MM:SS\n";
            
            bot.sendMessage(chat_id, welcome, "");
        }

        if (text == "/iniciar_tempo") {
        
            String response = "Tempo iniciado em " + formatTimeMMSS(getCountdown());
            
            startCountdown();
            bot.sendMessage(chat_id, response, "");
        }

        if (text == "/pausar_tempo") {
        
            String response = "Tempo pausado em " + formatTimeMMSS(getCountdown());
            
            pauseCountdown();
            bot.sendMessage(chat_id, response, "");
        }

        // if (text.startsWith("/adicionar_tempo")) {
        
        //     String response = "Medição atual da caixa de agua:\n";
        
        //     bot.sendMessage(chat_id, response, "");
        // }

        // if (text.startsWith("/diminuir_tempo")) {
        
        //     String response = "Medição atual da caixa de agua:\n";
        
        //     bot.sendMessage(chat_id, response, "");
        // }
        
        if (text.startsWith("/definir_tempo")) {
            String response = "Tempo definido para X segundos";
            
            bot.sendMessage(chat_id, response, "");
        }
   
        if (text.startsWith("/checar_tempo")) {            
            bot.sendMessage(chat_id, formatTimeMMSS(getCountdown()), "");
        }
    }
}

void setupBot(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
}

void comunicateToBot(){
    if (millis() > lastTimeBotRan + DELAY)  {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while(numNewMessages) {
        handleNewMessages(numNewMessages);
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        lastTimeBotRan = millis();
    }
}