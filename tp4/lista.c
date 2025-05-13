// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct item_t
{
    int valor;
    struct item_t *ant;
    struct item_t *prox;
} ;

// estrutura de uma lista
struct lista_t
{
    struct item_t *prim;
    struct item_t *ult;
    int tamanho;
} ;

struct lista_t *lista_cria (){
    struct lista_t *L;
    if (! (L = malloc(sizeof(struct lista_t))) )
        return NULL;
    
    L->prim = NULL;
    L->ult = NULL;
    L->tamanho = 0;

    return L;
}

int lista_insere (struct lista_t *lst, int item, int pos){
    if (lst == NULL)
        return -1;

    struct item_t *aux;

    struct item_t *nodo;
    if (! (nodo = malloc(sizeof(struct item_t))) )
        return -1;
    //inicializando o novo nodo
    nodo->ant = NULL;
    nodo->prox = NULL;
    nodo->valor = item;
    //lista vazia
    if (lst->tamanho == 0)
    {
        lst->prim = nodo;
        lst->ult = nodo;
        lst->tamanho++;

        return lst->tamanho;
    }    

    aux = lst->prim;

    //insere no inicio
    if (pos == 0)
    {
        nodo->prox = aux;
        aux->ant = nodo;
        lst->prim = nodo;

        aux = NULL;

        lst->tamanho++;

        return lst->tamanho;
    }

    //insere no fim
    if (pos > lst->tamanho || pos == -1)
    {
        aux = lst->ult;
        aux->prox = nodo;
        nodo->ant = aux;
        lst->ult = nodo;

        aux = NULL;

        lst->tamanho++;

        return lst->tamanho;
    }

    //insere no meio
    // contador == indice ou posicao do nodo na lista
    int contador = 0;
    //sai do laco quando chegar na posicao
    while (contador < pos)
    {
        aux = aux->prox;
        contador++;
    }
    
    nodo->ant = aux->ant;
    nodo->prox = aux;
    aux->ant->prox = nodo;
    aux->ant = nodo;

    aux = NULL;

    lst->tamanho++;

    return lst->tamanho;
}

struct lista_t *lista_destroi (struct lista_t *lst){
    struct item_t *aux;

    if (lst->tamanho < 0)
        return NULL;

    aux = lst->prim;

    while (aux != NULL)
    {
        struct item_t *temp = aux;
        //move para o proximo
        aux = aux->prox;
        //libera o atual
        free (temp);
        temp = NULL;
    }

    free (lst);
    lst = NULL;

    return NULL;
}

int lista_retira (struct lista_t *lst, int *item, int pos){
    if (lst == NULL || item == NULL)
        return -1;
    
    struct item_t *aux;
    int cont = 0;

    if (lst->tamanho == 0)
        return -1;
    //lista com um unico elemento
    if (lst->tamanho == 1)
    {
        aux = lst->prim;
        *item = aux->valor;
        lst->prim = NULL;
        lst->ult = NULL;
        lst->tamanho--;

        free (aux);
        aux = NULL;

        return lst->tamanho;
    }
    //remove do final
    if (pos >= lst->tamanho || pos == -1)
    {
        aux = lst->ult;
        *item = aux->valor;
        lst->ult = aux->ant;

        aux->ant->prox = NULL;

        free (aux);
        aux = NULL;

        lst->tamanho--;

        return lst->tamanho;
    }

    //remove primeiro elemento
    if (pos == 0)
    {
        aux = lst->prim;
        *item = aux->valor;
        lst->prim = aux->prox;
        aux->prox->ant = NULL;

        free (aux);
        aux = NULL;

        lst->tamanho--;

        return lst->tamanho;
    }

    //caminha ate chegar na posicao para retirar    
    aux = lst->prim;
    while (cont < pos)
    {
        aux = aux->prox;
        cont++;
    }
    // liga o antetior com o prox pulando o removido
    aux->ant->prox = aux->prox;
    aux->prox->ant = aux->ant;

    *item = aux->valor;

    free (aux);
    aux = NULL;

    lst->tamanho--;

    return lst->tamanho;
}

int lista_consulta (struct lista_t *lst, int *item, int pos){
    if (lst == NULL || item == NULL)
        return -1;
    struct item_t *aux;
    //posicao maior que quantidade de itens
    if (pos > (lst->tamanho - 1) || pos < -1)
        return -1;
    //remove do fim
    if ((pos == -1) || pos == (lst->tamanho))
    {
        aux = lst->ult;
        *item = aux->valor;

        aux = NULL;

        return lst->tamanho;
    }

    int cont = 0;
    aux = lst->prim;
    //caminha ate a posicao
    while (cont < pos)
    {
        aux = aux->prox;
        cont++;
    }    

    *item = aux->valor;

    aux = NULL;

    return lst->tamanho;
}

int lista_procura (struct lista_t *lst, int valor){
    if (lst == NULL)
        return -1;

    struct item_t *aux;
    aux = lst->prim;
    int tam = 0;
    while (tam < lst->tamanho)
    {
        if (aux->valor == valor)
            return tam;

        aux = aux->prox;
        tam ++;
    }

    return -1;
}

int lista_tamanho (struct lista_t *lst){
    if (lst == NULL || lst->tamanho < 0)
        return -1;

    return lst->tamanho;
}

void lista_imprime (struct lista_t *lst){
    struct item_t *aux;
    if (lst->prim == NULL)
        return;

    aux = lst->prim;
    printf ("%d", aux->valor);
    
    for (int i = 2; i <= lst->tamanho; i++)
    {
        aux = aux->prox;
        printf (" %d", aux->valor);
    }
    return;
}