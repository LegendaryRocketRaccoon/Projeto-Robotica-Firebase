#include "funcoes.h"
#include <Arduino.h>

void desligarTodosAtuadores() {
  digitalWrite(PINO_ESTEIRA, LOW);
  digitalWrite(PINO_SEPARADOR, LOW);
  digitalWrite(PINO_TRAVA, LOW);
  digitalWrite(PINO_MAGAZINE, LOW);
  digitalWrite(PINO_MEDIDOR, LOW);
}