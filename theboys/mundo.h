#ifndef MUNDO
#define MUNDO

#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>

// eventos
#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_VIAJA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_AVISA 7
#define EV_MORRE 8
#define EV_MISSAO 9
#define EV_FIM 10

// inicializacao mundo
#define T_FIM_MUNDO 525600 // MUDAR 525600
#define TAM_MUNDO 20000
#define NUM_HABILIDADES 10
#define NUM_HEROIS (NUM_HABILIDADES * 5)
#define NUM_BASES (NUM_HEROIS / 5)
#define NUM_MISSOES (T_FIM_MUNDO / 100)
#define NUM_COMPOSTOS_V (NUM_HABILIDADES * 3)

extern int ev_tratados;
extern int herois_mortos;

mundo_t *mundo_cria();

void inicia_herois(struct fprio_t *lef, mundo_t *mundo);

void inicia_missoes(struct fprio_t *lef, mundo_t *mundo);

#endif