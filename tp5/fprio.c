// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>

// A COMPLETAR

struct fpnodo_t
{
    void *item;
    int tipo;
    int prio;
    struct fpnodo_t *prox;
};

struct fprio_t
{
    struct fpnodo_t *prim;
    int num;
};

struct fprio_t *fprio_cria (){
    struct fprio_t *primeiro;
    if (! (primeiro = malloc(sizeof(struct fprio_t))) )
        return NULL;

    primeiro->prim = NULL;
    primeiro->num = 0;

    return primeiro;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
    if (f == NULL && item != NULL)
    {
        free (item);

        return -1;
    }
    if (f == NULL || item == NULL)
        return -1;
    struct fpnodo_t *novo;
    if (! (novo = malloc(sizeof(struct fpnodo_t))) )
        return -1;

    novo->item = item;
    novo->prio = prio;
    novo->prox = NULL;
    novo->tipo = tipo;
    //fila vazia
    if (f->num == 0)
    {
        f->prim = novo;
        f->num++;

        return f->num;
    }
    
    struct fpnodo_t *aux;
    aux = f->prim;
    //checa se o item foi inserido anteriormente
    while (aux != NULL)
    {
        if (aux->item == item)
        {
            free (novo);
            return -1;
        }
        aux = aux->prox;
    }

    if (prio < f->prim->prio)
    {
        novo->prox = f->prim;
        f->prim = novo;
        f->num++;

        return f->num;
    }

    //caminha se a prioridade for menor
    //para se chegar no ultimo item
    aux = f->prim;
    while (aux->prox != NULL && prio >= aux->prox->prio)
        aux = aux->prox;
    //insere o item
    novo->prox = aux->prox;
    aux->prox = novo;
    f->num++;

    return f->num;
}

struct fprio_t *fprio_destroi (struct fprio_t *f){
    struct fpnodo_t *aux;
    aux = f->prim;

    if (f == NULL || f->num < 0)
        return NULL;
    
    while (aux != NULL)
    {
        struct fpnodo_t *temp = aux;
        //move para o proximo
        aux = aux->prox;
        //libera o atual
        free (temp);
        temp = NULL;
    }

    free (f);
    f = NULL;

    return NULL;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
    if (f == NULL || f->num == 0 || tipo == NULL || prio == NULL)
    {
        tipo = NULL;
        prio = NULL;

        return NULL;
    }
  
    struct fpnodo_t *aux;
    aux = f->prim;

    //mais de um item na lista
    f->prim = aux->prox;
    f->num--;
    *tipo = aux->tipo;
    *prio = aux->prio;

    void *item;
    item = aux->item;

    free (aux);
    aux = NULL;

    return item;
}

int fprio_tamanho (struct fprio_t *f){
    if (f == NULL)
        return -1;

    return f->num;
}

void fprio_imprime (struct fprio_t *f){
    if (f == NULL || f->prim == NULL)
        return;

    struct fpnodo_t *aux;
    aux = f->prim;
    printf ("(%d %d)", aux->tipo, aux->prio);

    for (int i = 2; i <= f->num; i++)
    {
        aux = aux->prox;
        printf (" (%d %d)", aux->tipo, aux->prio);
    }
}