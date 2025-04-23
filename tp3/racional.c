/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"
/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b)
{
    while((a != 0) && (b != 0)){
        if(a > b)
            a = a % b;
        else 
            b = b % a;
    }
    if (a == 0)
        return b;
    else 
        return a;
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
    long resultado_mdc;

    resultado_mdc = mdc(labs(a), labs(b));
    if (resultado_mdc < 0)
        return -1;

    return ((a * b) / mdc (a, b));
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r (struct racional *r)
{
    if ((r->den == 0) || (r == NULL))
        return 0;

    long maior_multiplo = mdc(labs(r->num), labs(r->den));
    r->num = r->num / maior_multiplo;
    r->den = r->den / maior_multiplo;

    if (r->den < 0)
    { 
        r->den = r->den * -1;
        r->num = r->num * -1;
        /*inverte se deenominador for negativo*/
    }
    return 1;
}

int valido_r (struct racional *r)
{
    if ((r == NULL)||(r->den == 0))
        return 0;
    else 
        return 1;
}

int compara_r (struct racional *r1, struct racional *r2)
{

    if ((r1 == NULL) || (r2 == NULL))
        return -2;
    if ((!valido_r(r1)) || (!valido_r(r2)))
        return -2;

    if ((r1->num == r2->num)&&(r1->den == r2->den))
        return 0;

    int min_mult_comum;
    min_mult_comum = mmc(labs(r1->den),labs(r2->den));

    struct racional temp_r1,temp_r2;
    /* Calcula os numeradores equivalentes*/
    temp_r1.num = r1->num * (min_mult_comum/r1->den);
    temp_r2.num = r2->num * (min_mult_comum/r2->den);

    if ((temp_r1.num)<(temp_r2.num))
        return -1;
    if ((temp_r1.num)>(temp_r2.num))
        return 1;

    return 0;
}

void imprime_r (struct racional *r)
{
    if (r == NULL){
        printf ("NULL");
        return;
    }
    simplifica_r (r);
    if (r->den == 0){
        printf ("NaN");
        return;
    }
    if (r->num == 0){
        printf ("0");
        return;
    }
    if (r->num == r->den){
        printf ("1");
        return;
    }
    /*inverte se numerador e ou denominador forem negativos*/
    if (r->den < 0)
    { 
        r->den = r->den * -1;
        r->num = r->num * -1;
    }

    if (r->den == 1){
        printf ("%ld", r->num);
        return;
    }

    printf ("%ld/%ld", r->num, r->den);
    return;
}

struct racional *cria_r (long numerador, long denominador)
{
    struct racional *r;
    r = malloc (sizeof(struct racional));
    if (r == NULL)
        return NULL;

    r->num = numerador;
    r->den = denominador;

    return r;
}

int soma_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
    r3 -> num = r1->num*r2->den + r2->num*r1->den;
    r3 -> den = r1->den*r2->den;
    simplifica_r(r3);
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else 
        return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
    r3 -> num = r1->num*r2->den - r2->num*r1->den;
    r3 -> den = r1->den*r2->den;
    simplifica_r(r3);
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else 
        return 1;
}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
    r3 -> num = r1->num*r2->num;
    r3 -> den = r1->den*r2->den;
    simplifica_r(r3);
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else 
        return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
    r3 -> num = r1->num*r2->den;
    r3 -> den = r1->den*r2->num;
    simplifica_r(r3);
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else 
        return 1;
}

void destroi_r(struct racional *r) {
    if (r != NULL) {
        free(r);
        r = NULL;
    }
}

/* implemente as demais funções de racional.h aqui */
