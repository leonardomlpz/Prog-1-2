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
        base[i].base_presentes = cjto_cria(NUM_HEROIS);
        base[i].espera = fila_cria();
        //numero maximo de habilidades por heroi = 3 * qtde de herois maxima
        base[i].hab_presentes = cjto_cria(3*base[i].lotacao_max);
        base[i].distancia_missao = 0;
        base[i].qtde_missoes = 0;
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
        missao[i].id = i;
        missao[i].coord_x = aleat(0,TAM_MUNDO);
        missao[i].coord_y = aleat(0,TAM_MUNDO);
        missao[i].habilidades = cjto_aleat(aleat(6,10),NUM_HABILIDADES);
        missao[i].realizada = 0;
        missao[i].tentativas = 0;
    }

    return missao;
}

dist_t *cria_bases_distancias(mundo_t *mundo)
{
    dist_t *dist;
    if (! (dist = malloc(NUM_BASES*sizeof(dist_t))) )
        return NULL;

    for (int i = 0; i < NUM_BASES; i++)
    {
        dist[i].base_id = mundo->bases[i].base_id;
        dist[i].coord_x = mundo->bases[i].coord_x;
        dist[i].coord_y = mundo->bases[i].coord_y;
        dist[i].distancia = 0;
    }

    return dist;
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

    if (! (mundo->dist_miss_base = cria_bases_distancias(mundo)) )
    {
        printf("erro ao criar bases para distancia\n");
        return NULL;
    }

    // VER SE PRECISO COLOCAR NA STRUCT OS DEFINES
    mundo->num_compostoV = NUM_COMPOSTOS_V;
    mundo->num_missoes_cumpridas = 0;

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

void inicia_missoes(struct fprio_t *lef, mundo_t *mundo)
{
    evento_t *ev;
    int tempo;
    for (int i = 0; i < NUM_MISSOES; i++)
    {
        tempo = aleat(0,T_FIM_MUNDO);
        ev = itens(NULL,NULL,&mundo->missoes[i],tempo);
        fprio_insere(lef,ev,EV_MISSAO,ev->tempo);
    }
}

void destroi_base(base_t *base)
{
    if (base == NULL)
        return;
    
    if (base->base_presentes)
        cjto_destroi(base->base_presentes);
    
    if (base->espera)
        fila_destroi(base->espera);
    
    if (base->hab_presentes)
        cjto_destroi(base->hab_presentes);
}

void mundo_destroi(mundo_t *mundo)
{
    if (mundo == NULL)
        return;

    if (mundo->herois) 
    {
        for (int i = 0; i < NUM_HEROIS; i++)
            if (mundo->herois[i].habilidades)
                cjto_destroi(mundo->herois[i].habilidades);
        free(mundo->herois);
    }

    if (mundo->missoes) 
    {
        for (int i = 0; i < NUM_MISSOES; i++)
            if (mundo->missoes[i].habilidades)
                cjto_destroi(mundo->missoes[i].habilidades);
        free(mundo->missoes);
    }

    if (mundo->bases) {
        for (int i = 0; i < NUM_BASES; i++)
            destroi_base(&mundo->bases[i]);
        free(mundo->bases);
    }

    if (mundo->dist_miss_base)
        free(mundo->dist_miss_base);

    free(mundo);

    return;
}