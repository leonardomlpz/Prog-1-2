// programa principal do projeto "The Boys - 2025/1"
// Autor: Leonardo Martins Lopes, GRR 20242343

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "estruturas.h"
#include "mundo.h"
#include "eventos.h"
// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{
    //srand(time(NULL));
    srand(0);
    // iniciar o mundo

    struct fprio_t *lef;
    if (! (lef = malloc(sizeof(struct fprio_t))) )
        return 0;

    mundo_t *mundo;
    mundo = mundo_cria();
    inicia_herois(lef,mundo);
    inicia_missoes(lef,mundo);

    //base_t *bases_ordenadas;
    //if (! (bases_ordenadas = malloc(NUM_BASES*sizeof(base_t))) )
    //    return 0;
    //// cria uma copia das bases para reordenar a cada missao
    //memcpy(bases_ordenadas, mundo->bases, NUM_BASES*sizeof(base_t));

    // executar o laço de simulação
    evento_t *ev;

    ev = itens(NULL,NULL,NULL,0);
    fprio_insere(lef,ev,EV_FIM,T_FIM_MUNDO);

    int tipo,tempo;
    while (ev->tempo <= T_FIM_MUNDO)
    {
        ev = fprio_retira(lef,&tipo,&tempo);
        if (ev == NULL)
            break;
        
        switch (tipo)
        {
            case EV_CHEGA:
                chega(ev->tempo,ev->heroi,ev->base,lef);
                break;

            case EV_ESPERA:
                espera(ev->tempo,ev->heroi,ev->base,lef);
                break;

            case EV_DESISTE:
                desiste(ev->tempo,ev->heroi,ev->base,mundo,lef);
                break;

            case EV_VIAJA:
                viaja(ev->tempo,ev->heroi,ev->base,mundo,lef);
                break;

            case EV_ENTRA:
                entra(ev->tempo,ev->heroi,ev->base,lef);
                break;

            case EV_SAI:
                sai(ev->tempo,ev->heroi,ev->base,mundo,lef);
                break;

            case EV_AVISA:
                avisa(ev->tempo,ev->heroi,ev->base,lef);
                break;

            case EV_MISSAO:
                missao(ev->tempo,mundo,ev->missao,lef);
                break;

            case EV_MORRE:
                morre(ev->tempo,ev->heroi,ev->base,ev->missao,lef);
                break;

            case EV_FIM:
                break;

            default:
                break;
        }
    }

    // destruir o mundo
    return 0;
}

