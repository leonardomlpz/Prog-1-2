#include <stdio.h>
#include "mundo.h"
#include "estruturas.h"
#include "conjunto.h"

long aleat (long min, long max)
{
	return rand() % (max - min + 1) + min;
}

heroi_t *cria_herois()
{
    heroi_t *herois;
    if (! (herois = malloc(NUM_HEROIS*sizeof(heroi_t))) )
        return NULL;
    
    for (int i = 0; i < NUM_HEROIS; i++)
    {
        herois[i].heroi_id = aleat(0,NUM_BASES - 1);
        herois[i].exp = 0;
        herois[i].paciencia = aleat(0,100);
        herois[i].velocidade = aleat(50,5000);
        herois[i].habilidades = cjto_aleat(NUM_HABILIDADES,aleat(1,3));
        cjto_imprime(herois->habilidades);
    }
    return herois;
}

int mundo_cria()
{
    mundo_t *mundo;
    if (! (mundo = malloc(sizeof(mundo_t))) )
        return;
}