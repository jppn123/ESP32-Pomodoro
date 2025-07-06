#include <WebServer.h>
#include "countdown.h"
#include "util.h"

WebServer server(80);

// Task handle for the web server
TaskHandle_t serverTaskHandle = NULL;

// Task function for handling server clients
void serverTask(void *pvParameters) {
    for (;;) {
        server.handleClient();
        vTaskDelay(1 / portTICK_PERIOD_MS); // Yield to other tasks
    }
}

void setupWebServer() {
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
                    main.container {
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
                    section.timer-section {
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
                    .time-input {
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        gap: 10px;
                        margin-bottom: 20px;
                        flex-wrap: wrap;
                    }
                    input[type=number] {
                        padding: 8px;
                        font-size: 1rem;
                        width: 60px;
                        border: 1px solid #ccc;
                        border-radius: 5px;
                        text-align: center;
                    }
                    label {
                        font-size: 1rem;
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
                    .set-time-btn { background: #f4a261; color: #fff; }
                    .set-time-btn:hover { background: #e89b53; }
                    section.info-section {
                        margin-top: 40px;
                    }
                    section.info-section h2 {
                        color: #e76f51;
                        font-size: 1.8rem;
                        margin-bottom: 15px;
                    }
                    section.info-section p {
                        margin-bottom: 15px;
                        color: #444;
                    }
                    section.info-section ul,
                    section.info-section ol {
                        margin-left: 30px;
                        margin-bottom: 20px;
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
                    button:focus,
                    input:focus {
                        outline: 2px solid #e76f51;
                        outline-offset: 2px;
                    }
                </style>
            </head>
            <body>
                <main class="container" role="main">
                    <h1>Pomodoro ESP32 <span role="img" aria-label="tomate">🍅</span></h1>
                    <p class="subtitle">Maximize sua produtividade com a técnica Pomodoro</p>

                    <section class="timer-section" aria-labelledby="statusLabel">
                        <div id="status" class="status" role="status" aria-live="polite" aria-atomic="true">Carregando estado...</div>
                        <div id="time" class="time" role="timer" aria-live="off" aria-atomic="true">25:00</div>

                        <div class="time-input">
                            <label for="minutes">Minutos:</label>
                            <input type="number" id="minutes" min="0" max="59" placeholder="MM" value="20">
                            <label for="seconds">Segundos:</label>
                            <input type="number" id="seconds" min="0" max="59" placeholder="SS" value="00">
                            <button class="set-time-btn" onclick="setPomodoroTime()">Definir Tempo</button>
                        </div>

                        <div class="controls">
                            <button class="start-btn" onclick="controlPomodoro('start')">Iniciar</button>
                            <button class="pause-btn" onclick="controlPomodoro('pause')">Pausar</button>
                            <button class="reset-btn" onclick="controlPomodoro('reset')">Reiniciar</button>
                        </div>
                    </section>

                    <section class="info-section">
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
                        <ol>
                            <li>Escolha uma tarefa.</li>
                            <li>Inicie o temporizador (25 minutos).</li>
                            <li>Trabalhe sem interrupções até o alarme.</li>
                            <li>Faça uma pausa de 5 minutos.</li>
                            <li>Após 4 pomodoros, faça uma pausa longa (15–30 minutos).</li>
                        </ol>

                        <p class="references">
                            Referências:<br>
                            <a href="https://francescocirillo.com/pages/pomodoro-technique" target="_blank">Francesco Cirillo - Técnica Pomodoro</a><br>
                            <a href="https://www.forbes.com/sites/bryancollinseurope/2020/03/03/the-pomodoro-technique/" target="_blank">Forbes - The Pomodoro Technique</a>
                        </p>
                    </section>

                    <footer>
                        Desenvolvido com ESP32 | Jonatha Targino; João Pedro Barros © 2025
                    </footer>
                </main>

                <script>
                    let lastUpdateTime = 0;
                    async function updateData() {
                        let actState = "";
                        try {
                            const now = Date.now();
                            if (now - lastUpdateTime < 900) return;
                            lastUpdateTime = now;
                            const res = await fetch("/status");
                            const data = await res.json();
                            if(data.state == "updating") {
                                actState = "Ajustando tempo do Pomodoro";
                            } else if(data.state == "started") {
                                actState = "Pomodoro em andamento";
                            } else if(data.state == "restarted") {
                                actState = "Pomodoro reiniciado";
                            } else if(data.state == "updated") {
                                actState = "Tempo do Pomodoro atualizado";
                            } else {
                                actState = "Pomodoro pausado";
                            }
                            document.getElementById("status").innerText = actState;
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

                    async function setPomodoroTime() {
                        try {
                            const minutes = document.getElementById("minutes").value || 0;
                            const seconds = document.getElementById("seconds").value || 0;
                            await fetch(`/set-time?minutes=${minutes}&seconds=${seconds}`, { method: 'POST' });
                            updateData();
                        } catch (error) {
                            console.error('Erro ao definir tempo:', error);
                            document.getElementById("status").innerText = "Erro ao definir tempo";
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
        json += "\"state\": \"" + state + "\",";
        json += "\"time\": \"" + formatTimeMMSS(getCountdown()) + "\"";
        json += "}";
        server.send(200, "application/json", json);
    });

    server.on("/control", HTTP_POST, []() {
        if (server.hasArg("action")) {
            String action = server.arg("action");
            if (action == "start") {
                startCountdown();
                server.send(200, "text/plain", "Pomodoro iniciado");
            } else if (action == "pause") {
                pauseCountdown();
                server.send(200, "text/plain", "Pomodoro pausado");
            } else if (action == "reset") {
                setCountdown(20 * 60);
                pauseCountdown();
                server.send(200, "text/plain", "Pomodoro reiniciado");
            } else {
                server.send(400, "text/plain", "Ação inválida");
            }
        } else {
            server.send(400, "text/plain", "Ação não especificada");
        }
    });

    server.on("/set-time", HTTP_POST, []() {
        if (server.hasArg("minutes") && server.hasArg("seconds")) {
            int minutes = server.arg("minutes").toInt();
            int seconds = server.arg("seconds").toInt();
            if (minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59) {
                uint32_t totalSeconds = minutes * 60 + seconds;
                newCountdown(totalSeconds);
                setCountdown(totalSeconds);
                pauseCountdown(); // Pause after setting new time
                server.send(200, "text/plain", "Tempo definido");
            } else {
                server.send(400, "text/plain", "Valores de tempo inválidos");
            }
        } else {
            server.send(400, "text/plain", "Parâmetros de tempo não especificados");
        }
    });

    server.begin();
    Serial.println("Servidor HTTP iniciado: http://" + WiFi.localIP().toString());

    // Create a task for handling server clients
    xTaskCreatePinnedToCore(
        serverTask,           // Task function
        "ServerTask",        // Task name
        4096,                // Stack size (bytes)
        NULL,                // Task parameters
        1,                   // Priority
        &serverTaskHandle,   // Task handle
        1                    // Core (0 or 1, use 1 for web server to avoid core 0's WiFi tasks)
    );
}

void serverHandleClient() {
    // No longer needed in the main loop, handled by serverTask
}