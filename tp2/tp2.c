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
void quick_sort(struct racional vet[], int n){
    if (n <= 1)
        return;

    struct racional temp;
    int novo_pivo;

    int menor = 0;
    int maior = n - 1;

    //Escolhe o pivo como o ultimo elemento
    struct racional pivo = vet[maior];
    int i = menor - 1;

    //Particionamento
    for (int j = menor; j < maior; j++){
        if (compara_r(vet[j], pivo) < 0){
            i++;
            //troca vet[i] com vet[j]
            temp = vet[i];
            vet[i] = vet[j];
            vet[j] = temp;
        }
    }

    // coloca o pivo na posicao correta
    temp = vet[i + 1];
    vet[i + 1] = vet[maior];
    vet[maior] = temp;
    novo_pivo = i + 1;

    // recursao
    quick_sort(vet, novo_pivo); // parte esquerda
    quick_sort(vet + novo_pivo, n - novo_pivo - 1); // parte da direita
}

void le_vet(struct racional vetor[], long tam){
    long i,numerador,denominador;
    for(i = 0; i < tam; i++)
    {
        scanf("%ld %ld", &numerador, &denominador);
        vetor[i] = cria_r(numerador, denominador);
    }
    return;
}

void elimina_nulo(struct racional vetor[], long tam, long *qtde_nulos)
{
    int i,j,tam_temp;
    tam_temp = tam;
    for (i = 0; i < tam; i++)
    {
        if (valido_r(vetor[i]) == 0)
        {
            *qtde_nulos = *qtde_nulos + 1;
            for (j = tam_temp - 1; j > 1; j--)
            {
                if (valido_r(vetor[j]) != 0)
                {
                    vetor[i] = vetor[j];
                    tam_temp = j;
                    break;
                }
            }
        }
    }
}

void soma_vet(struct racional vetor[], long tam)
{
    struct racional soma;
    soma.num = 0;
    soma.den = 1;
    struct racional temp;
    for (int i = 0; i < tam; i++)
    {
        soma_r(vetor[i],soma,&temp);
        soma.num = temp.num;
        soma.den = temp.den;
    }
    imprime_r(soma);
}

void imprime_vet(struct racional vetor[], long tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf (" ");
        imprime_r(vetor[i]);
    }
}
/* programa principal */
int main ()
{
    long n,nulos;
    struct racional vetor[100];

    scanf("%ld", &n);

    le_vet(vetor,n);

    printf ("VETOR =");
    imprime_vet(vetor,n);
    printf ("\n");

    //eliminar os elementos invalidos do vetor
    nulos = 0;// quantidade de numeros nulos no vetor
    elimina_nulo(vetor,n,&nulos);

    printf ("VETOR =");
    if (nulos != n)
    {
        imprime_vet(vetor,n - nulos);
    }
    printf ("\n");

    //ordena vetor
    printf("VETOR =");
    if (nulos != n)
    {
        quick_sort(vetor,(n - nulos));
        imprime_vet(vetor,n - nulos);
    }
    printf ("\n");

    //soma vetor
    printf("SOMA =");
    if (nulos != n)
    {
        printf(" ");
        soma_vet(vetor,(n - nulos));
    }
    else printf(" 0");

    printf("\n");

    return (0) ;
}
