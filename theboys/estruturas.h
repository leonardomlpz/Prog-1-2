#ifndef ESTRUTURAS
#define ESTRUTURAS

#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

typedef struct heroi
{
    int heroi_id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int exp;
    int base;
    int vivo;
} heroi_t;

typedef struct base
{
    int base_id;
    int lotacao_max;
    struct cjto_t *base_presentes;
    struct fila_t *espera;
    int coord_x,cood_y;
    struct cjto_t *hab_presentes;
} base_t;

typedef struct missao
{
    int id;
    struct cjto_t *habilidades;
    int cood_x,cood_y;
} missao_t;

typedef struct mundo
{
    int num_herois;
    heroi_t *herois;
    int num_bases;
    base_t *bases;
    int num_missoes;
    missao_t *missoes;
    int num_hab;
    int num_compostoV;
    int cood_x,coord_y;
    int relogio;
} mundo_t;

typedef struct evento
{
    base_t *base;
    heroi_t *heroi;
    missao_t *missao;
    int tempo;
} evento_t;

#endif