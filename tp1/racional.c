/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
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

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
	while((a != 0) && (b != 0)){
		if(a > b)
			a = a % b;
		else b = b % a;
		}
		if (a == 0)
			return b;
		else return a;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
	long maior_mult = mdc(labs(r.num), labs(r.den));
	r.num = r.num / maior_mult;
	r.den = r.den / maior_mult;

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

struct racional soma_r (struct racional r1, struct racional r2)
{
	struct racional r;
	r.num = r1.num*r2.den + r2.num*r1.den;
	r.den = r1.den*r2.den;

	return r;
}

struct racional subtrai_r (struct racional r1, struct racional r2)
{
	struct racional r;
	r.num = r1.num*r2.den - r2.num*r1.den;
	r.den = r1.den*r2.den;

	return r;
}

struct racional multiplica_r (struct racional r1, struct racional r2)
{
	struct racional r;
	r.num = r1.num*r2.den - r2.num*r1.den;
	r.den = r1.den*r2.den;

	return r;
}

struct racional divide_r (struct racional r1, struct racional r2)
{
	struct racional r;
	r.num = r1.num*r2.den;
	r.den = r1.den*r2.num;

	return r;
}
/* implemente as demais funções aqui */

