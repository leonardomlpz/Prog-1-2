/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void le_vet(struct racional *vetor[], long tam)
{
    long i,numerador,denominador;

    for(i = 0; i < tam; i++)
    {
        scanf("%ld %ld", &numerador, &denominador);
        vetor[i] = cria_r(numerador, denominador);
    }
    return;
}

void imprime_vet(struct racional *vetor[], long tam)
{
    if (tam > 0)
        imprime_r(vetor[0]);

    for (int i = 1; i < tam; i++)
    {
        printf (" ");
        imprime_r(vetor[i]);
    }
}

void quick_sort(struct racional *vetor[], int n)
{
    if (n <= 1) {
        return; /* Se o vetor tiver tamanho 0 ou 1 já está ordenado */
    }

    int menor = 0;
    int maior = n - 1;

    /* Escolhe o pivô como o último elemento */
    struct racional *pivo = vetor[maior];
    int i = menor - 1;

    /* Particionamento */
    for (int j = menor; j < maior; j++) {
        if (compara_r(vetor[j], pivo) < 0) {
            i++;
            /* Troca vetor[i] e vetor[j] */
            struct racional *temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    /* Coloca o pivô na posição correta */
    struct racional *temp = vetor[i + 1];
    vetor[i + 1] = vetor[maior];
    vetor[maior] = temp;
    int novoPivo = i + 1;

    /* Recursividade*/ 
    quick_sort(vetor, novoPivo); /* Ordena a parte esquerda */
    quick_sort(vetor + novoPivo + 1, n - novoPivo - 1); /* Ordena a parte direita */
}

void troca_elemento(struct racional **a, struct racional **b)
{
    struct racional *temp = *a;
    *a = *b;
    *b = temp;
}

/*ordena trocando o primero nulo do comeco para o fim, pelo primeiro nao nulo
testando do fim para o comeco*/
void elimina_nulo(struct racional *vetor[], int *tam)
{
    int i, j;
    int qtde_nulos = 0;
    //coloca os elementos nulos no fim do vetor
    for (i = 0; i < *tam; i++)
    {
        if (valido_r(vetor[i]) == 0)
        {
            for (j = *tam - 1; j > i; j--)
            {
                if (valido_r(vetor[j]) != 0)
                {
                    troca_elemento(&vetor[i], &vetor[j]);
                    break;
                }
            }
        }
    }
    //elimina os nulos e conta a quantidade para decrementar o tamanho do vetor
    for (i = 0; i < *tam; i++)
    {
        if (!valido_r(vetor[i]))
        {
            qtde_nulos++;
            destroi_r(vetor[i]);
            vetor[i] = NULL;
        }
    }
    
    *tam -= qtde_nulos;
}


struct racional *soma_vet(struct racional *vetor[], long tam)
{
    struct racional *soma = malloc(sizeof(struct racional));
    struct racional temp;

    soma->num = 0;
    soma->den = 1;

    for (int i = 0; i < tam; i++)
    {
        soma_r(vetor[i],soma,&temp);
        soma->num = temp.num;
        soma->den = temp.den;
    }

    return soma;
}

void libera_vet(struct racional *vetor[], int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        destroi_r(vetor[i]);
        vetor[i] = NULL;
    }
}

/* programa principal */
int main ()
{
    int n;

    scanf ("%d", &n);

    struct racional **vetor;
    struct racional *soma;

    if (!(vetor  = malloc(n * sizeof(struct racional*))))
        return 0;

    le_vet(vetor,n);
    printf ("VETOR = ");
    imprime_vet(vetor,n);
    printf ("\n");

    elimina_nulo(vetor,&n);
    printf ("VETOR = ");
    imprime_vet(vetor,n);
    printf ("\n");

    quick_sort(vetor,n);
    printf ("VETOR = ");
    imprime_vet(vetor,n);
    printf ("\n");

    printf ("SOMA = ");
    //testa se apos eliminar nulos ainda tem elementos no vetor
    if (n > 0)
    {
        soma = soma_vet(vetor,n);
        imprime_r(soma);
        destroi_r(soma);
    }
    else
        printf ("0");
    printf ("\n"); 

    printf ("VETOR = ");
    libera_vet (vetor,n);  
    imprime_vet(vetor,n);

    printf ("\n");

    free (vetor);
    vetor = NULL;

    return (0) ;
}
