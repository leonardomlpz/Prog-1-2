#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

#include "fila.h"

struct fila_t *fila_cria ()
{
    struct fila_t *primeiro;
    if (! (primeiro = malloc(sizeof(struct fila_t))) )
        return NULL;

    primeiro->prim = NULL;
    primeiro->fim = NULL;
    primeiro->num = 0;

    return primeiro;
}

struct fila_t *fila_destroi (struct fila_t *f)
{
    struct fila_nodo_t *aux;
    aux = f->fim;

    if (f == NULL || f->num < 0)
        return NULL;

    struct fila_nodo_t *temp;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free (temp);
    }

    free (f);
    f = NULL;

    return NULL;
}

int fila_insere (struct fila_t *f, void *item)
{
    if (f == NULL && item != NULL)
    {
        free (item);

        return -1;
    }
    if (f == NULL || item == NULL)
        return -1;
    struct fila_nodo_t *novo;
    if (! (novo = malloc(sizeof(struct fila_nodo_t))) )
        return -1;

    novo->item = item;
    novo->prox = NULL;

    if (f->num == 0)
    {
        f->prim = novo;
        f->num++;
        f->fim = novo;

        return f->num;
    }

    struct fila_nodo_t *aux;
    aux = f->prim;
    //checagem se ja foi inserido anteriormente
    while (aux != NULL)
    {
        if (aux->item == item)
        {
            free (novo);

            return -1;
        }
        aux = aux->prox;
    }

    f->fim->prox = novo;
    f->fim = novo;
    f->num++;

    return f->num;
}

void *fila_retira (struct fila_t *f)
{
    if (f == NULL || f->num == 0 || f->prim->item == NULL)
        return NULL;

    struct fila_nodo_t *aux;
    aux = f->prim;

    f->prim = aux->prox;
    f->num--;

    void *item;
    item = aux->item;

    free (aux);
    aux = NULL;

    return item;
}

int fila_tamanho (struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return f->num;
}

void fila_imprime (struct fila_t *f)
{
    if (f == NULL || f->prim == NULL)
        return;

    struct fila_nodo_t *aux;
    aux = f->prim;
    printf ("(%d)", ((heroi_t *)aux->item)->heroi_id);

    for (int i = 2; i <= f->num; i++)
    {
        aux = aux->prox;
        printf (" (%d)", ((heroi_t *)aux->item)->heroi_id);
    }
}