#include <stdio.h>
#include "mundo.h"
#include "estruturas.h"
#include "conjunto.h"
#include "eventos.h"

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
        //jeito correto de utilizar cjto_aleat
        herois[i].habilidades = cjto_aleat(aleat(1,3),NUM_HABILIDADES);
        herois[i].heroi_id = i;
        herois[i].vivo = 1;
        herois[i].base_id = -1;
    }

    return herois;
}

base_t *cria_bases()
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
        base[i].espera = fila_cria();
        //numero maximo de habilidades por heroi = 3 * qtde de herois maxima
        base[i].base_presentes = cjto_cria(3*base[i].lotacao_max);
    }

    return base;
}

//missao_t *cria_missoes()

mundo_t *mundo_cria()
{
    mundo_t *mundo;
    if (! (mundo = malloc(sizeof(mundo_t))) )
        return NULL;

    if  (! (mundo->herois = cria_herois()) )
    {
        printf("erro ao criar herois\n");
        return NULL;
    }

    if (! (mundo->bases = cria_bases()) )
    {
        printf("erro ao criar bases\n");
        return NULL;
    }

    // VER SE PRECISO COLOCAR NA STRUCT OS DEFINES
    mundo->cood_x = TAM_MUNDO;
    mundo->coord_y = TAM_MUNDO;
    mundo->num_bases = NUM_BASES;
    mundo->num_compostoV = NUM_COMPOSTOS_V;
    mundo->num_hab = NUM_HABILIDADES;
    mundo->num_hab = NUM_HABILIDADES;
    mundo->num_herois = NUM_HEROIS;
    mundo->num_missoes = T_FIM_MUNDO;
    mundo->relogio = 0;

    return mundo;
}