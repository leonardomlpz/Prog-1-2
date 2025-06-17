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
        base[i].coord_y = aleat(0,TAM_MUNDO -1);
        base[i].lotacao_max = aleat(3,10);
        //base[i].base_presentes = cjto_cria(base[i].lotacao_max);
        base[i].base_presentes = cjto_cria(NUM_HEROIS);
        if (base[i].base_presentes == NULL)
        {
            printf("ERRO AO CRIAR CJTO\n");
            return NULL;
        }

        base[i].espera = fila_cria();
        //numero maximo de habilidades por heroi = 3 * qtde de herois maxima
        //base[i].hab_presentes = cjto_cria(3*base[i].lotacao_max);
        base[i].hab_presentes = cjto_cria(3*base[i].lotacao_max);
        base[i].distancia_missao = 0;
    }

    return base;
}

missao_t *cria_missoes()
{
    missao_t *missao;
    if (! (missao = malloc(NUM_MISSOES*sizeof(missao_t))) )
        return NULL;

    for (int i = 0; i < NUM_MISSOES; i++)
    {
        missao->id = i;
        missao->coord_x = aleat(0,TAM_MUNDO);
        missao->coord_y = aleat(0,TAM_MUNDO);
        missao->habilidades = cjto_aleat(aleat(6,10),NUM_HABILIDADES);
    }

    return missao;
}

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

    if (! (mundo->missoes = cria_missoes()) )
    {
        printf ("erro ao criar missoes\n");
        return NULL;
    }

    // VER SE PRECISO COLOCAR NA STRUCT OS DEFINES
    mundo->coord_x = TAM_MUNDO;
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

void inicia_herois(struct fprio_t *lef, mundo_t *mundo)
{
    evento_t *ev;
    int tempo, base;
    for (int i = 0; i < NUM_HEROIS; i++)
    {
        base = aleat(0, NUM_BASES -1);
        tempo = aleat(0,4320);
        ev = itens(&mundo->bases[base],&mundo->herois[i],NULL,tempo);
        fprio_insere(lef,ev,EV_CHEGA,ev->tempo);
    }

    return;
}