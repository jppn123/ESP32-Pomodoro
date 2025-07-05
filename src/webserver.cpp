#include <WiFi.h>
#include <WebServer.h>
#include "countdown.h"
#include "util.h"

WebServer server(80);

void setupWebServer() {
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.println("[WebServer] Aguardando conexão com Wi-Fi...");
    }

    server.on("/", HTTP_GET, []() {
        String html = R"rawliteral(
            <!DOCTYPE html>
            <html lang="pt-BR">
            <head>
                <meta charset="UTF-8">
                <title>Pomodoro ESP32</title>
                <meta name="viewport" content="width=device-width, initial-scale=1">
                <style>
                    body {
                        font-family: Arial, sans-serif;
                        background-color: #fdf6e3;
                        color: #333;
                        text-align: center;
                        padding-top: 50px;
                    }
                    .container {
                        background: #fff;
                        padding: 30px;
                        border-radius: 12px;
                        box-shadow: 0 0 10px rgba(0,0,0,0.1);
                        display: inline-block;
                        min-width: 280px;
                    }
                    h1 {
                        color: #e76f51;
                    }
                    .status {
                        font-size: 1.2rem;
                        margin-top: 10px;
                        color: #2a9d8f;
                    }
                    .time {
                        font-size: 3rem;
                        font-weight: bold;
                        margin-top: 20px;
                    }
                </style>
            </head>
            <body>
                <div class="container">
                    <h1>Pomodoro ESP32 🍅</h1>
                    <div class="status" id="status">Carregando estado...</div>
                    <div class="time" id="time">00:00</div>
                </div>

                <script>
                    async function updateData() {
                        const res = await fetch("/status");
                        const data = await res.json();
                        document.getElementById("status").innerText = data.running ? "Pomodoro em andamento" : "Pomodoro pausado";
                        document.getElementById("time").innerText = data.time;
                    }

                    setInterval(updateData, 1000);
                    updateData();
                </script>
            </body>
            </html>
        )rawliteral";

        server.send(200, "text/html", html);
    });

    server.on("/status", HTTP_GET, []() {
        String json = "{";
        json += "\"running\": " + String(isRunning ? "true" : "false") + ",";
        json += "\"time\": \"" + formatTimeMMSS(getCountdown()) + "\"";
        json += "}";
        server.send(200, "application/json", json);
    });

    server.begin();
    Serial.println("Servidor HTTP iniciado: http://" + WiFi.localIP().toString());
}

void serverHandleClient() {
    server.handleClient(); 
}