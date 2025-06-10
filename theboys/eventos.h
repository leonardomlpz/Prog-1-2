#ifndef EVENTOS
#define EVENTOS

#include "estruturas.h"

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