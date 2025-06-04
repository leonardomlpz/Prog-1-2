#ifndef EVENTOS
#define EVENTOS

#include "estruturas.h"

#define ev_chega 1
#define ev_espera 2
#define ev_desiste 3
#define ev_viaja 4
#define ev_entra 5
#define ev_sai 6
#define ev_avisa 7
#define ev_morre 8
#define  ev_missao 9
#define ev_fim 10

int aleat (int min, int max);

evento_t *itens(base_t *base, heroi_t *heroi, missao_t *missao, int tempo);

void chega(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef);

void espera(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef);

void desiste(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef);

void avisa(int tempo, heroi_t *heroi,base_t *base,struct fprio_t *lef);

void entra(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef);

void sai(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef);

void viaja(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef);

void morre(int tempo, heroi_t *heroi, base_t *base,struct missao *missao, struct fprio_t *lef);

void missao(int tempo,mundo_t *mundo, struct missao *missao, struct fprio_t *lef);

void fim(mundo_t *mundo);

#endif