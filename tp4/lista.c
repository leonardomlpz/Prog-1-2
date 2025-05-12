// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

struct item_t
{
    int valor;
    struct item_t *ant;
    struct item_t *prox;
} ;

// estrutura de uma lista
struct lista_t
{
    struct item_t *prim;
    struct item_t *ult;
    int tamanho;
} ;
