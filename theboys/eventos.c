#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eventos.h"
#include "mundo.h"

int ev_tratados = 0;
int herois_mortos = 0;

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
    ev_tratados++;
    evento_t *temp;
    temp = itens(base,heroi,NULL,tempo);

    int esperar;

    heroi->base_id = base->base_id;

    if (base->espera->num == 0 && base->lotacao_max > base->base_presentes->num)
        esperar = 1;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->num);

    if (esperar)
    {
        fprio_insere(lef,temp,EV_ESPERA,temp->tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->lotacao_max);
    }
    else
    {
        fprio_insere(lef,temp,EV_DESISTE,temp->tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->lotacao_max);
    }
    return;
}

void espera(int tempo, heroi_t *heroi, base_t *base, struct fprio_t *lef)
{
    ev_tratados++;
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, heroi->heroi_id, base->base_id, base->espera->num);
    
    base->espera->num = fila_insere(base->espera,heroi);

    evento_t *temp;
    temp = itens(base,heroi,NULL,tempo);
    fprio_insere(lef,temp,EV_AVISA,temp->tempo);

    return;
}

void desiste(int tempo, heroi_t *heroi, base_t *base, mundo_t *mundo, struct fprio_t *lef)
{
    ev_tratados++;
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroi->heroi_id, base->base_id);

    base_t *destino;
    destino = &mundo->bases[aleat(0,NUM_BASES - 1)];

    evento_t *temp;
    temp = itens(destino,heroi,NULL,tempo);
    fprio_insere(lef,temp,EV_VIAJA,temp->tempo);

    return;
}

void avisa(int tempo, heroi_t *heroi, base_t *base, struct fprio_t *lef)
{
    ev_tratados++;
    if (!heroi->vivo)
        return;
    
    evento_t *temp;
    heroi_t *temp_heroi;

    printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [", tempo, base->base_id, base->base_presentes->num, base->lotacao_max);
    fila_imprime(base->espera);
    printf("]\n");

    while (base->lotacao_max > base->base_presentes->num && base->espera->num > 0)
    {
        // testa se houve erro na remocao
        if (! (temp_heroi = fila_retira(base->espera)) )
            break;
        if ((cjto_insere(base->base_presentes,temp_heroi->heroi_id)) == -1)
        {
            printf ("ERRO AO INSERIR HEROI (%d) NA BASE (%d)\n", temp_heroi->heroi_id,base->base_id);
            return;
        }

        temp = itens(base,temp_heroi,NULL,tempo);
        fprio_insere(lef,temp,EV_ENTRA,temp->tempo);

        printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, base->base_id, temp_heroi->heroi_id);
    }
    return;
}

void entra(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef)
{
    ev_tratados++;
    int tpb;

    //calcula tpb = tempo de permanência na base:
    tpb = 15 + heroi->paciencia * aleat(1,20);
    
    printf ("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->lotacao_max, tempo+tpb);

    struct cjto_t *temporaria;
    //adicao das hab do heroi ao cjto da base
    //temporaria recebe as habilidades dos herois + das bases
    temporaria = cjto_uniao(base->hab_presentes,heroi->habilidades);
    //destroi cjto antigo
    cjto_destroi(base->hab_presentes);
    //base recebe novo conjunto com habilidades atualizadas
    base->hab_presentes = temporaria;
    
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
    evento_t *temp;
    temp = itens(base,heroi,NULL,tempo + tpb);
    fprio_insere(lef,temp,EV_SAI,temp->tempo);

    return;
}

//remove as habilidades antigas e confere se removeu alguma que nao deveria
void remove_hab_heroi(heroi_t *heroi, base_t *base, mundo_t *mundo)
{
    struct cjto_t *temp;
    if (!(temp = cjto_dif(base->hab_presentes,heroi->habilidades)))
        return;
    
    cjto_destroi(base->hab_presentes);
    base->hab_presentes = temp;

    for (int i = 0; i < NUM_HEROIS; i++)
    {
        if (cjto_pertence(base->base_presentes,mundo->herois[i].heroi_id) == 1)
        {
            temp = cjto_uniao(base->hab_presentes,mundo->herois[i].habilidades);
            cjto_destroi(base->hab_presentes);
            base->hab_presentes = temp;
        }
    }
}

void sai(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef)
{
    ev_tratados++;
    if (cjto_retira(base->base_presentes,heroi->heroi_id) == -1)
        return;

    //remove as habilidades do heroi da base
    remove_hab_heroi(heroi,base,mundo);

    evento_t *evento1;
    evento_t *evento2;
    //calcula a base destino
    evento1 = itens(&mundo->bases[aleat(0,NUM_BASES -1)],heroi,NULL,tempo);
    fprio_insere(lef,evento1,EV_VIAJA,evento1->tempo);
    //muda para base da chamada da funcao para entrar o ev avisa
    evento2 = itens(base,heroi,NULL,tempo);
    fprio_insere(lef,evento2,EV_AVISA,evento2->tempo);

    printf ("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, heroi->heroi_id, base->base_id, base->base_presentes->num, base->lotacao_max);

    return;
}

void viaja(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef)
{
    ev_tratados++;
    base_t origem = mundo->bases[heroi->base_id];
    double dx,dy;
    double distancia;
    double duracao;

    dx = origem.coord_x - base->coord_x;
    dy = origem.coord_y - base->coord_y;
    distancia = sqrt(dx * dx + dy * dy);
    duracao = distancia / heroi->velocidade;

    printf("%6d: VIAJA HEROI %2d BASE %2d BASE %2d DIST %.2f VEL %d CHEGA %.2f\n", tempo, heroi->heroi_id, heroi->base_id, base->base_id, distancia, heroi->velocidade, tempo + duracao);

    evento_t *temp = itens(base, heroi, NULL, tempo + duracao);

    fprio_insere(lef, temp, EV_CHEGA, temp->tempo);

    return;
}

void morre(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo ,missao_t *missao, struct fprio_t *lef)
{
    ev_tratados++;
    herois_mortos++;
    cjto_retira(base->base_presentes, heroi->heroi_id);

    remove_hab_heroi(heroi,base,mundo);

    heroi->vivo = 0;

    evento_t *temp;
    temp = itens(base,heroi,missao,tempo);
    fprio_insere(lef,temp,EV_AVISA,temp->tempo);

    printf ("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, heroi->heroi_id, missao->id);

    return;
}

//algoritmo simples para ordenar um vetor de bases pequeno
//Ordena as bases com base nas distancias
void bubblesort(dist_t *vetor, int tam)
{
    int i, j;
    dist_t temp;
    for (i = 0; i < tam -1; i++)
    {
        for (j = 0; j < tam - i - 1; j++)
        {
            if (vetor[j].distancia > vetor[j + 1].distancia)
            {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

//Procura a base mais proxima / testa se pode ser feita a missao na base
//Retorno indice da base que pode realizar ou -1 se nao pode realizar
int bmp(mundo_t *mundo, missao_t *missao, dist_t *base_ordenada, int *dist)
{
    int indice = 0;
    float distancia = 0;
    int pode_ser_realizada = -1;
    //calcula as distancias das bases em relacao a missao
    for (int i = 0; i < NUM_BASES; i++)
    {
        distancia = sqrt((pow(missao->coord_x - base_ordenada[i].coord_x, 2) + pow(missao->coord_y - base_ordenada[i].coord_y, 2)));
        base_ordenada[i].distancia = distancia;
    }

    bubblesort(base_ordenada,NUM_BASES);
    
    for (int i = 0; i < NUM_BASES; i++)
    {
        indice = base_ordenada[i].base_id;
        if (cjto_contem(mundo->bases[indice].hab_presentes, missao->habilidades) == 1)
        {
            //pode_ser_realizada = base_ordenada[i].base_id;
            pode_ser_realizada = mundo->bases[indice].base_id;
            *dist = base_ordenada[i].distancia;
            break;
        }
    }

    return pode_ser_realizada;
}

void missao(int tempo,mundo_t *mundo, struct missao *missao, struct fprio_t *lef)
{
    ev_tratados++;
    evento_t *temp;
    int pode_ser_realizada;
    int distancia_missao;
    heroi_t *heroi_mais_exp;
    base_t *base_capaz;

    missao->tentativas++;
    printf ("%6d: MISSAO %d TENT %d HAB REQ: [",tempo, missao->id,missao->tentativas);
    cjto_imprime(missao->habilidades);
    printf ("]\n");

    pode_ser_realizada = bmp(mundo,missao,mundo->dist_miss_base,&distancia_missao);

    if (pode_ser_realizada > -1)
    {
        missao->realizada = 1;
        mundo->num_missoes_cumpridas++;
        mundo->bases[pode_ser_realizada].qtde_missoes++;

        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [", tempo, missao->id, mundo->bases[pode_ser_realizada].base_id,distancia_missao);
        cjto_imprime(mundo->bases[pode_ser_realizada].base_presentes);
        printf("]\n");

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [",tempo,missao->id,mundo->bases[pode_ser_realizada].base_id);
        cjto_imprime(mundo->bases[pode_ser_realizada].hab_presentes);
        printf("]\n");

        for (int i = 0; i < NUM_HEROIS; i++)
        {
            if (mundo->herois[i].vivo)
                //testa se o heroi esta na base que realizou a missao
                if (cjto_pertence(mundo->bases[pode_ser_realizada].base_presentes,mundo->herois[i].heroi_id) == 1)
                {
                    mundo->herois[i].exp++;
                    printf ("%6d: MISSAO %d HAB HEROI %2d: [",tempo, missao->id, mundo->herois[i].heroi_id);
                    cjto_imprime(mundo->herois[i].habilidades);
                    printf ("]\n");
                }
            
        }
    }
    else
    {
        if (mundo->num_compostoV > 0 && ((tempo % 2500) == 0))
        {
            missao->realizada = 1;
            mundo->num_missoes_cumpridas++;
            //base capaz = base mais proxima da missao
            for (int i = 0; i < NUM_BASES; i++)
            {
                base_capaz = &mundo->bases[mundo->dist_miss_base[i].base_id];
                if (base_capaz->base_presentes->num > 0)
                    break;
            }
            if (!base_capaz)
            {
                printf("%6d: MISSAO %d FALHOU: nenhuma base com heróis vivos disponível para COMPOSTO V\n", tempo, missao->id);
                return;
            }
            base_capaz->qtde_missoes++;

            printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [",tempo,missao->id,base_capaz->base_id);
            cjto_imprime(base_capaz->hab_presentes);
            printf("]\n");

            heroi_mais_exp = NULL;
            mundo->num_compostoV--;
            missao->realizada = 1;

            //confere se heroi esta na base mais proxima
            //acha o heroi mais experiente na bmp
            for (int i = 0; i < NUM_HEROIS; i++)
            {
                if (cjto_pertence(base_capaz->base_presentes, mundo->herois[i].heroi_id) == 1)
                    if(!heroi_mais_exp || mundo->herois[i].exp > heroi_mais_exp->exp)
                        heroi_mais_exp = &mundo->herois[i];
            }
            
            if (heroi_mais_exp != NULL)
            {
                temp = itens(base_capaz,heroi_mais_exp,missao,tempo);
                fprio_insere(lef,temp,EV_MORRE,tempo);
            }

            for (int i = 0; i < NUM_HEROIS; i++)
                if (mundo->herois[i].vivo)
                    if (cjto_pertence(base_capaz->base_presentes,mundo->herois[i].heroi_id) == 1)
                    {
                        mundo->herois[i].exp++;
                        printf ("%6d: MISSAO %d HAB HEROI %2d: [",tempo, missao->id, mundo->herois[i].heroi_id);
                        cjto_imprime(mundo->herois[i].habilidades);
                        printf ("]\n");
                    }
        }
        else
        {
            temp = itens(NULL,NULL,missao,tempo + 24*60);
            fprio_insere(lef, temp, EV_MISSAO, temp->tempo);

            printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo,missao->id);
        }
    }

    return;
}

void fim(mundo_t *mundo)
{
    ev_tratados++;
    heroi_t *h_temp;
    base_t *b_temp;
    int tentativas_min, tentativas_max;
    float media_tentativas;
    int soma = 0;

    for (int i = 0; i < NUM_HEROIS; i++)
    {
        h_temp = &mundo->herois[i];
        if (h_temp->vivo)
        {
            printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [",h_temp->heroi_id,h_temp->paciencia,h_temp->velocidade,h_temp->exp);
            cjto_imprime(h_temp->habilidades);
            printf("]\n");
        }
        else
        {
            printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [",h_temp->heroi_id,h_temp->paciencia,h_temp->velocidade,h_temp->exp);
            cjto_imprime(h_temp->habilidades);
            printf("]\n");
        }
    }

    for (int i = 0; i < NUM_BASES; i++)
    {
        b_temp = &mundo->bases[i];
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",b_temp->base_id,b_temp->lotacao_max,b_temp->espera->num,b_temp->qtde_missoes);
    }

    printf("EVENTOS TRATADOS: %d\n", ev_tratados);
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", mundo->num_missoes_cumpridas, NUM_MISSOES, (float) (100 * mundo->num_missoes_cumpridas)/NUM_MISSOES);

    tentativas_min = mundo->missoes[0].tentativas;
    tentativas_max = mundo->missoes[0].tentativas;
    for (int i = 1; i < NUM_MISSOES; i++)
    {
        if (tentativas_min > mundo->missoes[i].tentativas)
            tentativas_min = mundo->missoes[i].tentativas;
        
        if (tentativas_max < mundo->missoes[i].tentativas)
            tentativas_max = mundo->missoes[i].tentativas;
    }
    for (int i = 0; i < NUM_MISSOES; i++)
        soma += mundo->missoes[i].tentativas;

    media_tentativas = (float)soma / NUM_MISSOES;

    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", tentativas_min, tentativas_max, media_tentativas);

    printf("TAXA MORTALIDADE: %.1f%%\n",(float) (100 * herois_mortos)/NUM_HEROIS);
}