#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"

int aleat (int min, int max)
{
    return reand() % (max - min + 1) + min;
}

evento_t *itens(base_t *base, heroi_t *heroi, missao_t *missao, int tempo)
{
    evento_t *elementos;
    if (! (elementos = malloc(sizeof(evento_t))) )
        return NULL;

    elementos->base = base;
    elementos->heroi = heroi;
    elementos->missao = missao;
    elementos->tempo = tempo;

    return elementos;
}