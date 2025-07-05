#include <Arduino.h>
#include <vector>
#include "bot.h"
#include "wifiCred.h"
#include "countdown.h"
#include "util.h"
#include "logs.h"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long lastTimeBotRan;

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
            welcome += "/definir_tempo {tempo} - Insere um valor para o contador no formato HH:MM:SS\n";
            welcome += "/iniciar_tempo - Inicia o tempo decrementando o contador\n";
            welcome += "/pausar_tempo - Pausa o contador\n";
            welcome += "/checar_logs - Verifica histórico de ações sobre o timer\n";
            
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

        if (text.startsWith("/definir_tempo")) {
            int spaceIndex = text.indexOf(' ');
            if (spaceIndex == -1) {
                bot.sendMessage(chat_id, "Formato inválido. Use: /definir_tempo MM:SS", "");
                return;
            }
        
            String timeParam = text.substring(spaceIndex + 1); // pega "01:20"
        
            int totalSeconds = parseTimeMMSS(timeParam);
            if (totalSeconds < 0) {
                bot.sendMessage(chat_id, "Formato de tempo inválido. Use MM:SS (ex: 05:30)", "");
                return;
            }
        
            setCountdown(totalSeconds); // sua função para setar o tempo
            String response = "Tempo definido para " + formatTimeMMSS(totalSeconds);
            bot.sendMessage(chat_id, response, "");
        }
   
        if (text.startsWith("/checar_tempo")) {            
            bot.sendMessage(chat_id, formatTimeMMSS(getCountdown()), "");
        }

        if (text.startsWith("/checar_logs")) {
            bot.sendMessage(chat_id, readLastLogs(10), "");
        }
    }
}

void setupBot(){
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
    initFS();
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