/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */
    
    int n, max;
    struct racional r1, r2;
    struct racional soma, sub, div, mul;

    scanf("%d %d", &n, &max);

    for (int i = 1; i <= n; i++)
    {
        printf("%d :", i);
        
        r1 = sorteia_r(-max, max);
        r2 = sorteia_r(-max, max);

        imprime_r(r1);
        imprime_r(r2);

        if ((valido_r(r1) == 0) || (valido_r(r2) == 0))
        {
            printf(" NUMERO INVALIDO\n");
            return 1;
        }

        soma = soma_r(r1, r2);
        sub = subtrai_r(r1, r2);
        div = divide_r(r1, r2);
        mul = multiplica_r(r1, r2);

        if (!valido_r(div))
        {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }
        imprime_r(soma);
        imprime_r(sub);
        imprime_r(mul);
        imprime_r(div);
        printf("\n");
    }

    return (0) ;
}
