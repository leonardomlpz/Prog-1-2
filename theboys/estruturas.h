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
    int base_id;
    int vivo;
} heroi_t;

typedef struct distancia_missoes_bases
{
    int base_id;
    int coord_x;
    int coord_y;
    float distancia;
} dist_t;

typedef struct base
{
    int base_id;
    int lotacao_max;
    struct cjto_t *base_presentes;
    struct fila_t *espera;
    int coord_x,coord_y;
    struct cjto_t *hab_presentes;
    int distancia_missao;
    int qtde_missoes;
} base_t;

typedef struct missao
{
    int id;
    struct cjto_t *habilidades;
    int coord_x,coord_y;
    int realizada;
    int tentativas;
} missao_t;

typedef struct mundo
{
    heroi_t *herois;
    base_t *bases;
    missao_t *missoes;
    int num_compostoV;
    dist_t *dist_miss_base;
    int num_missoes_cumpridas;
} mundo_t;

typedef struct evento
{
    base_t *base;
    heroi_t *heroi;
    missao_t *missao;
    int tempo;
} evento_t;

#endif