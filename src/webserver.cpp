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
                        font-family: 'Helvetica Neue', Arial, sans-serif;
                        background-color: #fef8e6;
                        color: #333;
                        margin: 0;
                        padding: 20px;
                        line-height: 1.6;
                    }
                    .container {
                        max-width: 800px;
                        margin: 0 auto;
                        background: #fff;
                        padding: 30px;
                        border-radius: 15px;
                        box-shadow: 0 4px 20px rgba(0,0,0,0.1);
                    }
                    h1 {
                        color: #e76f51;
                        text-align: center;
                        font-size: 2.5rem;
                        margin-bottom: 10px;
                    }
                    .subtitle {
                        text-align: center;
                        color: #555;
                        font-size: 1.1rem;
                        margin-bottom: 30px;
                    }
                    .timer-section {
                        text-align: center;
                        padding: 20px;
                        background: #f9f9f9;
                        border-radius: 10px;
                        margin-bottom: 30px;
                    }
                    .time {
                        font-size: 4.5rem;
                        font-weight: bold;
                        color: #2a9d8f;
                        margin: 10px 0;
                    }
                    .status {
                        font-size: 1.3rem;
                        color: #264653;
                        margin-bottom: 20px;
                    }
                    .controls {
                        display: flex;
                        justify-content: center;
                        gap: 15px;
                        margin-top: 20px;
                    }
                    button {
                        padding: 10px 20px;
                        font-size: 1rem;
                        border: none;
                        border-radius: 5px;
                        cursor: pointer;
                        transition: background 0.3s;
                    }
                    .start-btn { background: #2a9d8f; color: #fff; }
                    .start-btn:hover { background: #21867a; }
                    .pause-btn { background: #e76f51; color: #fff; }
                    .pause-btn:hover { background: #d65f43; }
                    .reset-btn { background: #264653; color: #fff; }
                    .reset-btn:hover { background: #1e3a47; }
                    .info-section {
                        margin-top: 40px;
                    }
                    .info-section h2 {
                        color: #e76f51;
                        font-size: 1.8rem;
                        margin-bottom: 15px;
                    }
                    .info-section p {
                        margin-bottom: 15px;
                        color: #444;
                    }
                    .info-section ul {
                        list-style-type: disc;
                        padding-left: 30px;
                        margin-bottom: 20px;
                    }
                    .info-section li {
                        margin-bottom: 10px;
                    }
                    .references {
                        font-size: 0.9rem;
                        color: #666;
                    }
                    .references a {
                        color: #2a9d8f;
                        text-decoration: none;
                    }
                    .references a:hover {
                        text-decoration: underline;
                    }
                    footer {
                        text-align: center;
                        margin-top: 40px;
                        color: #777;
                        font-size: 0.9rem;
                    }
                </style>
            </head>
            <body>
                <div class="container">
                    <h1>Pomodoro ESP32 🍅</h1>
                    <p class="subtitle">Maximize sua produtividade com a técnica Pomodoro</p>

                    <div class="timer-section">
                        <div class="status" id="status">Carregando estado...</div>
                        <div class="time" id="time">25:00</div>
                        <div class="controls">
                            <button class="start-btn" onclick="controlPomodoro('start')">Iniciar</button>
                            <button class="pause-btn" onclick="controlPomodoro('pause')">Pausar</button>
                            <button class="reset-btn" onclick="controlPomodoro('reset')">Reiniciar</button>
                        </div>
                    </div>

                    <div class="info-section">
                        <h2>Sobre a Técnica Pomodoro</h2>
                        <p>A técnica Pomodoro, desenvolvida por Francesco Cirillo no final dos anos 1980, é um método de gerenciamento de tempo que promove a produtividade e o foco. Ela divide o trabalho em intervalos de 25 minutos, chamados "pomodoros", seguidos por pausas curtas de 5 minutos. Após quatro pomodoros, faz-se uma pausa mais longa de 15-30 minutos.</p>
                        
                        <h3>Benefícios do Pomodoro</h3>
                        <ul>
                            <li><strong>Melhora o Foco:</strong> Intervalos curtos ajudam a manter a concentração, reduzindo distrações.</li>
                            <li><strong>Reduz a Fadiga:</strong> Pausas regulares previnem o esgotamento mental.</li>
                            <li><strong>Aumenta a Produtividade:</strong> Metas claras para cada pomodoro incentivam a conclusão de tarefas.</li>
                            <li><strong>Gerencia o Tempo:</strong> Ajuda a estimar melhor o tempo necessário para tarefas.</li>
                        </ul>

                        <h3>Como Usar</h3>
                        <p>
                            1. Escolha uma tarefa.<br>
                            2. Inicie o temporizador (25 minutos).<br>
                            3. Trabalhe sem interrupções até o alarme.<br>
                            4. Faça uma pausa de 5 minutos.<br>
                            5. Após 4 pomodoros, faça uma pausa longa (15-30 minutos).
                        </p>

                        <p class="references">
                            Referências:<br>
                            <a href="https://francescocirillo.com/pages/pomodoro-technique" target="_blank">Francesco Cirillo - Técnica Pomodoro</a><br>
                            <a href="https://www.forbes.com/sites/bryancollinseurope/2020/03/03/the-pomodoro-technique/" target="_blank">Forbes - The Pomodoro Technique</a>
                        </p>
                    </div>

                    <footer>
                        Desenvolvido para ESP32 | Técnica Pomodoro © 2025
                    </footer>
                </div>

                <script>
                    async function updateData() {
                        try {
                            const res = await fetch("/status");
                            const data = await res.json();
                            document.getElementById("status").innerText = data.running ? "Pomodoro em andamento" : "Pomodoro pausado";
                            document.getElementById("time").innerText = data.time;
                        } catch (error) {
                            document.getElementById("status").innerText = "Erro ao carregar estado";
                        }
                    }

                    async function controlPomodoro(action) {
                        try {
                            await fetch(`/control?action=${action}`, { method: 'POST' });
                            updateData();
                        } catch (error) {
                            console.error('Erro ao enviar comando:', error);
                        }
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