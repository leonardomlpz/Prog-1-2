#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eventos.h"
#include "mundo.h"

long aleat (int min, int max)
{
    return rand() % (max - min + 1) + min;
}
//Coloca os itens necessarios para usar na LEF em uma estrutura
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

    heroi->base_id = base->base_id;

    if (base->espera->num == 0 && base->lotacao_max > base->base_presentes->num)
        esperar = 0;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->num);

    if (esperar == 0)
    {
        fprio_insere(lef,temp,EV_ESPERA,temp->tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->base_presentes->cap);
    }
    else
    {
        fprio_insere(lef,temp,EV_DESISTE,temp->tempo);

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
    fprio_insere(lef,temp,EV_AVISA,temp->tempo);

    return;
}

void desiste(int tempo, heroi_t *heroi, base_t *base, mundo_t *mundo, struct fprio_t *lef)
{
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroi->heroi_id, base->base_id);

    base_t *destino;
    destino = &mundo->bases[aleat(0,mundo->num_bases - 1)];

    evento_t *temp;
    temp = itens(destino,heroi,NULL,tempo);
    fprio_insere(lef,temp,EV_VIAJA,temp->tempo);

    return;
}

void avisa(int tempo, heroi_t *heroi, base_t *base, struct fprio_t *lef)
{
    if (!heroi->vivo)
        return;
    
    evento_t *temp;
    heroi_t *temp_heroi;

    printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, base->base_id, base->base_presentes->num, base->lotacao_max);
    fila_imprime(base->espera);
    printf("]\n");

    while (base->lotacao_max > base->base_presentes->num && base->espera->num > 0)
    {
        // testa se houve erro na remocao
        if (! (temp_heroi = fila_retira(base->espera)) )
            break;
        if ((cjto_insere(base->base_presentes,temp_heroi->heroi_id)) == -1)
            return;
        // REMOCAO DAS INCREMENTACOES DIRETO NA FILA

        temp = itens(base,temp_heroi,NULL,tempo);
        fprio_insere(lef,temp,EV_ENTRA,temp->tempo);

        printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, base->base_id, heroi->heroi_id);
    }
    return;
}

void entra(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef)
{
    int tpb;

    //calcula tpb = tempo de permanência na base:
    tpb = 15 + heroi->paciencia * aleat(1,20);
    
    //insere o id na base, incrementa a qtde na funcao
    base->qtde_presentes = cjto_insere(base->base_presentes,heroi->heroi_id);
    if (base->qtde_presentes == -1)
    {
        printf ("ERRO AO INSERIR HEROI (%d) NA BASE (%d)\n", heroi->heroi_id,base->base_id);
        return;
    }

    cjto_imprime(base->base_presentes);
    printf("\n");
    cjto_imprime(base->hab_presentes);
    printf("\n");


    printf ("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, heroi->heroi_id, base->base_id, base->qtde_presentes, base->lotacao_max, tempo+tpb);
    //base->presentes->num++;
    
    //adicao das hab do heroi ao cjto da base
    struct cjto_t *temporaria;
    //temporaria recebe as habilidades dos herois + das bases
    temporaria = cjto_uniao(base->hab_presentes,heroi->habilidades);
    //destroi cjto antigo
    cjto_destroi(base->hab_presentes);
    //base recebe novo conjunto com habilidades atualizadas
    base->hab_presentes = temporaria;
    
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
    evento_t *temp;
    temp = itens(base,heroi,NULL,tpb);
    fprio_insere(lef,temp,EV_SAI,temp->tempo);

    return;
}

void sai(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef)
{
    if (cjto_retira(base->base_presentes,heroi->heroi_id) == -1)
        return;

    //remove as habilidades do heroi da base
    struct cjto_t *temp;
    if (!(temp = cjto_dif(base->hab_presentes,heroi->habilidades)))
        return;
    
    cjto_destroi(base->hab_presentes);
    base->hab_presentes = temp;

    evento_t *evento;
    //calcula a base destino
    evento = itens(&mundo->bases[aleat(0,NUM_BASES -1)],heroi,NULL,tempo);
    fprio_insere(lef,evento,EV_VIAJA,evento->tempo);
    //muda para base da chamada da funcao para entrar o ev avisa
    evento->base = base;
    fprio_insere(lef,evento,EV_AVISA,evento->tempo);

    printf ("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->lotacao_max);

    return;
}

void viaja(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef)
{
    base_t origem = mundo->bases[heroi->base_id];

    float distancia = sqrt(pow(origem.coord_x - base->coord_x, 2) + pow(origem.coord_y - base->coord_y, 2));
    float duracao = distancia / heroi->velocidade;

    printf("%6d: VIAJA HEROI %2d BASE %2d BASE %2d DIST %.2f VEL %d CHEGA %.2f\n", tempo, heroi->heroi_id, heroi->base_id, base->base_id, distancia, heroi->velocidade, tempo + duracao);

    evento_t *temp = itens(base, heroi, NULL, tempo + duracao);

    fprio_insere(lef, temp, EV_CHEGA, temp->tempo);

    return;
}

void morre(int tempo, heroi_t *heroi, base_t *base,struct missao *missao, struct fprio_t *lef)
{
    cjto_retira(base->base_presentes, heroi->heroi_id);

    struct cjto_t *cjto_temp;
    cjto_temp = cjto_dif(base->hab_presentes,heroi->habilidades);
    cjto_destroi(base->hab_presentes);
    base->hab_presentes = cjto_temp;

    heroi->vivo = 0;

    evento_t *temp;
    temp = itens(base,heroi,missao,tempo);
    fprio_insere(lef,temp,EV_AVISA,temp->tempo);

    printf ("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, heroi->heroi_id, missao->id);

    return;
}

void bubblesort(base_t *vetor, int tam)
{
    int i, j;
    base_t temp;
    for (i = 0; i < tam -1; i++)
    {
        for (j = 0; j < tam - i - 1; j++)
        {
            if (vetor[j].distancia_missao > vetor[j + 1].distancia_missao)
            {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

//Procura a base mais proxima / testa se pode ser feita a missao na base
//Ordena as bases com base nas distancias
//Retorno indice da base que pode realizar ou 0 se nao pode realizar
int bmp(mundo_t *mundo, missao_t *missao, base_t *base_ordenada)
{
    float distancia = 0;
    int pode_ser_realizada = 0;

    for (int i = 0; i < NUM_BASES; i++)
    {
        distancia = sqrt((pow(missao->coord_x - mundo->bases[i].coord_x, 2) + pow(missao->coord_y - mundo->bases[i].coord_y, 2)));
        //criar um vetor igual para ordenar as bases com base nas missoes
        base_ordenada[i].distancia_missao = distancia;
    }

    bubblesort(base_ordenada,NUM_BASES);
    
    for (int i = 0; i < NUM_BASES; i++)
    {
        if (cjto_contem(base_ordenada[i].hab_presentes, missao->habilidades))
        {
            pode_ser_realizada = base_ordenada[i].base_id;
            break;
        }
    }

    return pode_ser_realizada;
}

void missao(int tempo,mundo_t *mundo, struct missao *missao, struct fprio_t *lef, base_t *base_ordenada)
{
    evento_t *temp;
    int pode_ser_realizada;
    heroi_t *mais_exp;

    pode_ser_realizada = bmp(mundo,missao,base_ordenada);

    if (pode_ser_realizada)
    {
        missao->realizada = 1;
        for (int i = 0; i < NUM_HEROIS; i++)
            mundo->herois[i].exp++;
    }
    else
    {
        if (mundo->num_compostoV > 0 && ((tempo % 2500) == 0))
        {
            mundo->num_compostoV--;
            missao->realizada = 1;
            mais_exp = &mundo->herois[0];
            for (int i = 1; i < NUM_HEROIS; i++)
            {
                if (mais_exp->exp < mundo->herois[i].exp)
                    mais_exp = &mundo->herois[i];
            }
            temp = itens(NULL,mais_exp,missao,tempo);
            fprio_insere(lef,temp,EV_MORRE,tempo);

            for (int j = 0; j < NUM_HEROIS; j++)
                if (mundo->herois[j].vivo)
                    mundo->herois[j].exp++;
        }
        else
        {
            temp = itens(NULL,NULL,missao,tempo + 24*60);
            fprio_insere(lef, temp, EV_MISSAO, temp->tempo);
        }
    }
}