#include <Arduino.h>
#include <WiFi.h>

#include "pinos.h"
#include "estados.h"
#include "funcoes.h"
#include "estado_maquina.h"
#include "firebase.h"  // Novo arquivo que iremos criar

// Wi-Fi para acesso à internet
#define WIFI_SSID "R2D2"
#define WIFI_PASSWORD "Procyon Lotor"

Estado estadoAtual = MANUAL;
unsigned long startTime = 0;
unsigned long contadorMetal = 0;
unsigned long contadorPlastico = 0;

void setup() {
  Serial.begin(9600);
  startTime = millis();

  // Configuração dos pinos de entrada e saída
  pinMode(PINO_ESTEIRA, OUTPUT);
  pinMode(PINO_SEPARADOR, OUTPUT);
  pinMode(PINO_TRAVA, OUTPUT);
  pinMode(PINO_MAGAZINE, OUTPUT);
  pinMode(PINO_MEDIDOR, OUTPUT);

  pinMode(ENTRADA_VP, INPUT);
  pinMode(ENTRADA_VN, INPUT);
  pinMode(ENTRADA_D34, INPUT);
  pinMode(ENTRADA_D32, INPUT);

  desligarTodosAtuadores();

  // Conectar ao Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao Wi-Fi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicializar conexão com Firebase
  inicializarFirebase();
}

void loop() {
  verificarComandosFirebase();       // Verifica comandos recebidos do Firebase
  atualizarEstado();                // Atualiza o estado da máquina, se automático
  enviarEstadoParaFirebase();       // Envia dados (tempo e contadores) para o Firebase
  delay(300);
}