#ifndef ESTADOS_H
#define ESTADOS_H

enum Estado
{
  MANUAL,
  AUTOMATICO_EM_EXECUCAO,
  ESTADO_1,
  ESTADO_2,
  ESTADO_3,
  ESTADO_4,
  ESTADO_5,
  ESTADO_6,
  ESTADO_7,
  ESTADO_8
};

extern Estado estadoAtual;
extern unsigned long startTime;
extern unsigned long contadorMetal;
extern unsigned long contadorPlastico;

#endif
