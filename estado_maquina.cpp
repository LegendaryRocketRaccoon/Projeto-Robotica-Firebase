// estado_maquina.cpp
#include "estado_maquina.h"
#include "estados.h"
#include "pinos.h"
#include <Arduino.h>

void atualizarEstado() {
if (estadoAtual == MANUAL)
    return;

  delay(300);

  switch (estadoAtual)
  {
  case AUTOMATICO_EM_EXECUCAO:
    Serial.println("Iniciando processo automático...");
    estadoAtual = ESTADO_1;
    break;

  case ESTADO_1:
    if (digitalRead(ENTRADA_VP) == HIGH)
    {
      digitalWrite(PINO_MEDIDOR, LOW);
      digitalWrite(PINO_ESTEIRA, HIGH); // Liga esteira.
      digitalWrite(PINO_TRAVA, LOW);    // Ativa pino/trava.
      Serial.println("Peça detectada no início. Esteira ligada.");
      estadoAtual = ESTADO_2;
    }
    break;

  case ESTADO_2:
    if (digitalRead(ENTRADA_D32) == HIGH)
    {
      bool ehMetal = digitalRead(ENTRADA_VN) == LOW;
      digitalWrite(PINO_SEPARADOR, ehMetal ? LOW : HIGH); // Ativa separador se for metal.
      Serial.println(ehMetal ? "Peça não metálica detectada." : "Peça metálica. Separador ativado.");
      estadoAtual = ESTADO_3;
    }
    break;

  case ESTADO_3:
    digitalWrite(PINO_MAGAZINE, HIGH); // Ativa magazine.
    Serial.println("Magazine avançando.");
    delay(2000);
    estadoAtual = ESTADO_4;
    break;

  case ESTADO_4:
    digitalWrite(PINO_MAGAZINE, LOW); // Para magazine.
    Serial.println("Pino/trava ativada./Para magazine.");
    estadoAtual = ESTADO_5;
    break;

  case ESTADO_5:
    delay(2000);
    digitalWrite(PINO_TRAVA, HIGH); // Desativa pino/trava.
    delay(2000);
    digitalWrite(PINO_MAGAZINE, HIGH); // Ativa magazine.
    Serial.println("Magazine ativado./Pino desativado.");
    estadoAtual = ESTADO_6;
    break;

  case ESTADO_6:
    if (digitalRead(ENTRADA_D34) == HIGH)
    { // Sensor final detecta peça.
      Serial.println("Peça chegou ao final da esteira.");
      if (digitalRead(PINO_SEPARADOR) == HIGH)
      {
        contadorMetal++;
      }
      else if (digitalRead(PINO_SEPARADOR) == LOW)
      {
        contadorPlastico++;
      }
      estadoAtual = ESTADO_7;
    }
    break;

  case ESTADO_7:
    delay(2000);
    digitalWrite(PINO_MAGAZINE, LOW); // Para magazine.
    delay(2000);
    digitalWrite(PINO_ESTEIRA, LOW); // Desliga esteira.
    delay(2000);
    digitalWrite(PINO_SEPARADOR, LOW); // Desativa separador.
    delay(2000);
    Serial.println("Magazine desligado. Esteira desligada. Separador desativado.");
    estadoAtual = ESTADO_8;
    break;

  case ESTADO_8:
    Serial.println("Retornando ao modo manual.");
    estadoAtual = MANUAL;
    break;

  default:
    break;

    delay(1000);
  }
}