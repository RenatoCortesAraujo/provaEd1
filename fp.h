#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H


typedef struct{
    int chave;
    int prioridade;
} Item;

typedef struct No {
    Item dado;
    struct No *prox, *ant; // prox -> (Nó proximo), ant -> (Nó anterior)
} No;

typedef struct {
    No *cabeca; // maior prioridade
    No *calda; // menor prioridade
    int tamanho;
} FP;

FP* fila_criar(void);
void fila_destruir(FP **ref);
int fila_inserir(FP *fila, Item x);
int fila_remover_max(FP *fila, Item *out);
int fila_topo(const FP *fila, Item *out);
int fila_atualizar(FP *fila, int item, int nova_prioridade);
int fila_remover_item(FP *fila, int item, Item *out);
int fila_vazia(const FP *fila);
int fila_tamanho(const FP *fila);
void fila_listar(const FP *fila);

#endif