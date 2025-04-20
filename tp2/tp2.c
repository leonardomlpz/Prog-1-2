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

void quick_sort(struct racional vetor[], int n) {
    if (n <= 1) {
        return; /* Se o vetor tiver tamanho 0 ou 1 já está ordenado */
    }

    int menor = 0;
    int maior = n - 1;

    /* Escolhe o pivô como o último elemento */
    struct racional pivo = vetor[maior];
    int i = menor - 1;

    /* Particionamento */
    for (int j = menor; j < maior; j++) {
        if (compara_r(vetor[j], pivo) < 0) {
            i++;
            /* Troca vetor[i] e vetor[j] */
            struct racional temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    /* Coloca o pivô na posição correta */
    struct racional temp = vetor[i + 1];
    vetor[i + 1] = vetor[maior];
    vetor[maior] = temp;
    int novoPivo = i + 1;

    /* Recursividade*/ 
    quick_sort(vetor, novoPivo); /* Ordena a parte esquerda */
    quick_sort(vetor + novoPivo + 1, n - novoPivo - 1); /* Ordena a parte direita */
}

void le_vet(struct racional vetor[], long tam){
    long i, numerador, denominador;
    for(i = 0; i < tam; i++) {
        scanf("%ld %ld", &numerador, &denominador);
        vetor[i] = cria_r(numerador, denominador);
    }
    return;
}

    /* Elimina nulos percorrendo uma unica vez, troca o primeiro nao nulo
    com o ultimo elemento valido, assim ate um laço encontrar o outro*/
void elimina_nulo(struct racional vetor[], long tam, long *qtde_nulos) {
    int i, j, tam_temp;
    tam_temp = tam;
    for (i = 0; i < tam; i++) {
        if (valido_r(vetor[i]) == 0) {
            *qtde_nulos = *qtde_nulos + 1;
            for (j = tam_temp - 1; j > 1; j--) {
                if (valido_r(vetor[j]) != 0) {
                    vetor[i] = vetor[j];
                    tam_temp = j;
                    break;
                }
            }
        }
    }
}

void soma_vet(struct racional vetor[], long tam) {
    struct racional soma;
    soma.num = 0;
    soma.den = 1;
    struct racional temp;
    for (int i = 0; i < tam; i++) {
        soma_r(vetor[i], soma, &temp);
        soma.num = temp.num;
        soma.den = temp.den;
    }
    imprime_r(soma);
}  

void imprime_vet(struct racional vetor[], long tam) {
    for (int i = 0; i < tam; i++) {
        printf(" ");
        imprime_r(vetor[i]);
    }
}

/* programa principal */
int main() {
    long n, nulos;
    struct racional vetor[100];

    scanf("%ld", &n);

    le_vet(vetor, n);

    printf("VETOR =");
    imprime_vet(vetor, n);
    printf("\n");

    /*eliminar os elementos invalidos do vetor*/
    nulos = 0; /* quantidade de numeros nulos no vetor*/
    elimina_nulo(vetor, n, &nulos);

    printf("VETOR =");
    if (nulos != n) {
        imprime_vet(vetor, n - nulos);
    }
    printf("\n");

    /*ordena vetor*/
    printf("VETOR =");
    if (nulos != n) {
        quick_sort(vetor, (n - nulos));
        imprime_vet(vetor, n - nulos);
    }
    printf("\n");

    /*soma vetor*/
    printf("SOMA =");
    if (nulos != n) {
        printf(" ");
        soma_vet(vetor, (n - nulos));
    } else {
        printf(" 0");
    }

    printf("\n");

    return 0;
}
