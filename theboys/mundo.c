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
        herois[i].heroi_id = i;
        herois[i].vivo = 1;
    }

    return herois;
}

base_t *bases()
{
    base_t *base;
    if (! (base = malloc(NUM_BASES*sizeof(base_t))) )
        return NULL;

    for (int i = 0; i < NUM_BASES; i++)
    {
        base[i].base_id = i;
        base[i].coord_x = aleat(0,TAM_MUNDO -1);
        base[i].cood_y = aleat(0,TAM_MUNDO -1);
        base[i].lotacao_max = aleat(3,10);
        base[i].base_presentes = cjto_cria(base[i].lotacao_max);
    }
}

mundo_t *mundo_cria()
{
    mundo_t *mundo;
    if (! (mundo = malloc(sizeof(mundo_t))) )
        return;

    if  (! (mundo->herois = cria_herois()) );
        return -1;
}