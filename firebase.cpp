#include <Firebase_ESP_Client.h> // ou <FirebaseESP32.h> dependendo da versão instalada
#include <Arduino.h>
#include "firebase.h"
#include "estados.h"
#include "pinos.h"
#include "funcoes.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define API_KEY "AIzaSyAdKDXizjq1CKXLMocwbqMAgF3cvS6aYn4"
#define DATABASE_URL "https://projetoglo-default-rtdb.firebaseio.com/"

String pathComando = "/comando";
String pathEstado = "/estado";
String pathTempo = "/tempo";
String pathMetal = "/contador/metal";
String pathPlastico = "/contador/plastico";

void inicializarFirebase() {
    Serial.println("Iniciando Firebase...");
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = "raccoon@gmail.com";
  auth.user.password = "ProcyonLotor";
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase inicializado.");
}

void verificarComandosFirebase() {
    String comando;
    if (Firebase.RTDB.getString(&fbdo, pathComando, &comando)) {
        if (comando.length() > 0) {
            Serial.print("Comando recebido do Firebase: ");
            Serial.println(comando);

            if (comando == "ligarProcesso") {
                startTime = millis();
                estadoAtual = AUTOMATICO_EM_EXECUCAO;
            } else if (comando == "ligarEsteira") {
                digitalWrite(PINO_ESTEIRA, HIGH);
            } else if (comando == "desligarEsteira") {
                digitalWrite(PINO_ESTEIRA, LOW);
            } else if (comando == "ligarSeparador") {
                digitalWrite(PINO_SEPARADOR, HIGH);
            } else if (comando == "desligarSeparador") {
                digitalWrite(PINO_SEPARADOR, LOW);
            } else if (comando == "ligarTrava") {
                digitalWrite(PINO_TRAVA, HIGH);
            } else if (comando == "desligarTrava") {
                digitalWrite(PINO_TRAVA, LOW);
            } else if (comando == "ligarMedidor") {
                digitalWrite(PINO_MEDIDOR, HIGH);
            } else if (comando == "desligarMedidor") {
                digitalWrite(PINO_MEDIDOR, LOW);
            } else if (comando == "ligarMagazine") {
                digitalWrite(PINO_MAGAZINE, HIGH);
            } else if (comando == "desligarMagazine") {
                digitalWrite(PINO_MAGAZINE, LOW);
            }

            // Limpa o comando após executar
            Firebase.RTDB.setString(&fbdo, pathComando, "");
        }
    }
}

void enviarEstadoParaFirebase() {
    unsigned long tempoDecorrido = (estadoAtual == AUTOMATICO_EM_EXECUCAO || estadoAtual >= ESTADO_1)
                                       ? (millis() - startTime) / 1000
                                       : 0;

    Firebase.RTDB.setInt(&fbdo, pathTempo, tempoDecorrido);
    Firebase.RTDB.setInt(&fbdo, pathMetal, contadorMetal);
    Firebase.RTDB.setInt(&fbdo, pathPlastico, contadorPlastico);
}

void atualizarEstado() {
    if (estadoAtual == AUTOMATICO_EM_EXECUCAO) {
        if (millis() - startTime >= 10000) {
            estadoAtual = static_cast<Estado>((estadoAtual + 1) % 9);
            Serial.print("Mudando para o estado: ");
            Serial.println(estadoAtual);
        }
    } else if (estadoAtual == MANUAL) {
    }
}

void finalizarProcesso() {
    unsigned long tempoFinal = (millis() - startTime) / 1000;
    Firebase.RTDB.pushInt(&fbdo, "/historico_tempos", tempoFinal);
    Firebase.RTDB.setInt(&fbdo, "/tempo", 0);
}