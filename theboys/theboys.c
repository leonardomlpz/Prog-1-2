// programa principal do projeto "The Boys - 2025/1"
// Autor: Leonardo Martins Lopes, GRR 20242343

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "estruturas.h"
#include "mundo.h"
#include "eventos.h"
// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{
    srand(time(NULL));
    // iniciar o mundo

    mundo_t *mundo;
    mundo = mundo_cria();

    // executar o laço de simulação

    // destruir o mundo

}

