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

void chega(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef)
{
    evento_t *temp;
    temp = itens(base,heroi,NULL,tempo);

    int esperar;

    heroi->base = base->base_id;

    if (base->espera->num == 0 && base->lotacao_max > base->base_presentes->num)
        esperar = 0;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->num);

    if (esperar == 0)
    {
        fprio_insere(lef,temp,ev_espera,temp->tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->base_presentes->cap);
    }
    else
    {
        fprio_insere(lef,temp,ev_desiste,temp->tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->base_presentes->cap);
    }
    return;
}

void espera(int tempo, heroi_t *heroi, base_t *base, struct fprio_t *lef)
{
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, heroi->heroi_id, base->base_id, base->espera->num);
    
    base->espera->num = fila_insere(base->espera,heroi);

    evento_t *temp;
    temp = itens(base,heroi,NULL,tempo);
    fprio_insere(lef,temp,ev_avisa,temp->tempo);

    return;
}

void desiste(int tempo, heroi_t *heroi, base_t *base, mundo_t *mundo, struct fprio_t *lef)
{
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroi->heroi_id, base->base_id);

    base_t *destino;
    destino = &mundo->bases[aleat(0,mundo->num_bases - 1)];

    evento_t *temp;
    temp = itens(destino,heroi,NULL,tempo);
    fprio_insere(lef,temp,ev_viaja,temp->tempo);

    return;
}

void avisa(int tempo, heroi_t *heroi, base_t *base, struct fprio_t *lef)
{
    if (!heroi->vivo)
        return;
    
    evento_t *temp;

    printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, base->base_id, base->base_presentes->num, base->lotacao_max);
    fila_imprime(base->espera);
    printf("]\n");

    while (base->lotacao_max > base->base_presentes->num && base->espera->num > 0)
    {
        fila_retira(base->espera);
        if ((cjto_insere(base->espera,heroi->heroi_id)) == -1)
            return;
        base->base_presentes->num++;
        base->espera->num--;

        temp = itens(base,heroi,NULL,tempo);
        fprio_insere(lef,temp,ev_entra,temp->tempo);

        printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, base->base_id, heroi->heroi_id);
    }
    return;
}

void entra(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef)
{
    int tpb;
    //calcula tpb = tempo de permanência na base:
    tpb = 15 + heroi->paciencia * aleat(1,20);
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
    printf ("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->lotacao_max, tempo+tpb);

    //insere o id na base, incrementa a qtde na funcao
    cjto_insere(base->base_presentes,heroi->heroi_id);
    //base->presentes->num++;

    //adicao das hab do heroi ao cjto da base
    base->hab_presentes=cjto_uniao(base->hab_presentes,heroi->habilidades);

    //struct cjto_t *temporaria;
    //temporaria = cjto_uniao(base->hab_presentes,heroi->habilidades);
    //apaga cjto antigo
    cjto_destroi(base->hab_presentes);
    //base recebe novo conjunto com habilidades atualizadas
    //base->hab_presentes = temporaria;//TESTAR SE O PONTEIRO AINDA RECEBE ALGO

    struct evento *temp;
    temp = itens(base,heroi,NULL,tempo);
    fprio_insere(lef,temp,ev_sai,temp->tempo + tpb);

    return;
}