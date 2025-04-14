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

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
    return rand() % (max - min + 1) + min;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
    long tmp_a,tmp_b;
	tmp_a = labs(a);
	tmp_b = labs(b);
	while((tmp_a != 0) && (tmp_b != 0)){
		if(tmp_a > tmp_b)
			tmp_a = tmp_a % tmp_b;
		else tmp_b = tmp_b % tmp_a;
		}
		if (tmp_a == 0)
			return tmp_b;
		else return tmp_a;
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
    long resultado;

    resultado = mdc(a, b);
	if (resultado < 0)
		return -1;

	return ((a * b) / resultado);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
    if (r.den == 0)
        return r;

    long maior_mult = mdc(r.num, r.den);
    r.num = r.num / maior_mult;
    r.den = r.den / maior_mult;
    return r;
}

int valido_r (struct racional r)
{
	//retorna 1 se for valido
	if (r.den != 0)
		return 1;

	return 0;
}

struct racional cria_r (long numerador, long denominador)
{
	struct racional r;
	r.num = numerador;
	r.den = denominador;
	
	return r;
}

struct racional sorteia_r (long min, long max)
{
	struct racional r;
	long num = aleat(min, max);
	long den = aleat(min, max);

	r = cria_r(num, den);
	simplifica_r(r);

	return r;
}

void imprime_r (struct racional r)
{
	r = simplifica_r(r);

	if (r.den == 0){
		printf (" INVALIDO");
		return;
	}
	if (r.num == 0){
		printf (" 0");
		return;
	}
	if (r.num == r.den){
		printf (" 1");
		return;
	}
	//inverte se o den for negativo
	if (r.den < 0){
		r.num = r.num * -1;
		r.den = r.den * -1;
	}
	if (r.den == 1){
		printf (" %ld", r.num);
		return;
	}
	printf (" %ld/%ld", r.num, r.den);
	return;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{
    r3 -> num = r1.num*r2.den + r2.num*r1.den;
    r3 -> den = r1.den*r2.den;
    *r3 = simplifica_r(*r3);
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{
    r3 -> num = r1.num*r2.den - r2.num*r1.den;
    r3 -> den = r1.den*r2.den;
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
    r3 -> num = r1.num*r2.num;
    r3 -> den = r1.den*r2.den;
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
    r3 -> num = r1.num*r2.den;
    r3 -> den = r1.den*r2.num;
    if (valido_r(r1)==0 || (valido_r(r2)==0) || r3 == NULL)
        return 0;
    else return 1;
}

int compara_r (struct racional r1, struct racional r2)
{
    if (valido_r(r1) || valido_r(r2))
        return -2;

    if ((r1.num == r2.num) && (r1.den == r2.den))
        return 0;

    int min_mult;
    min_mult = mmc(r1.den, r2.den);

    r1.num = r1.num * (min_mult/r1.den);
    r2.num = r2.num * (min_mult/r2.den);

    if ((r1.num) < (r2.num))
        return -1;
    if ((r1.num) > (r2.num))
        return 1;

    return 0;
}