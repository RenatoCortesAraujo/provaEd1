#include <stdio.h>
#include <stdlib.h>
#include "fp.h"

FP* fila_criar(void) {
    FP *fila = (FP*)malloc(sizeof(FP));
    if (!fila) return NULL;
    fila->cabeca = fila->calda = NULL;
    fila->tamanho = 0;
    return fila;
}

void fila_destruir(FP **ref) {
    No *p;
    No *prox;
    if (!ref || !*ref) return;
    p = (*ref)->cabeca;
    while (p) {
        prox = p->ant;
        free(p);
        p = prox;
    }
    free(*ref);
    *ref = NULL;
}

int fila_inserir(FP *fila, Item x) {
    No *q;
    No *novo;
    No *p;
    if (!fila) return 0;

    q = fila->cabeca;
    while (q) {
        if (q->dado.chave == x.chave) return 0;
        q = q->prox;
    }

    novo = (No*)malloc(sizeof(No));
    novo->dado = x;
    novo->prox = novo->ant = NULL;

    if (fila->cabeca == NULL) {
        fila->cabeca = fila->calda = novo;
    } else {
        p = fila->cabeca;
        while (p && p->dado.prioridade >= x.prioridade)
            p = p->prox;

        if (!p) {
            novo->ant = fila->calda;
            fila->calda->prox = novo;
            fila->calda = novo;
        } else if (p == fila->cabeca) {
            novo->prox = fila->cabeca;
            fila->cabeca->ant = novo;
            fila->cabeca = novo;
        } else {
            novo->prox = p;
            novo->ant = p->ant;
            p->ant->prox = novo;
            p->ant = novo;
        }
    }

    fila->tamanho++;
    return 1;
}

int fila_remover_max(FP *fila, Item *out) {
    No *rem;
    if (!fila || !fila->cabeca) return 0;

    rem = fila->cabeca;
    *out = rem->dado;
    fila->cabeca = rem->prox;
    if (fila->cabeca) fila->cabeca->ant = NULL;
    else fila->calda = NULL;

    free(rem);
    fila->tamanho--;
    return 1;
}

int fila_topo(const FP *fila, Item *out) {
    if (!fila || !fila->cabeca) return 0;
    *out = fila->cabeca->dado;
    return 1;
}

int fila_atualizar(FP *fila, int chave, int nova_prioridade) {
    No *p;
    Item temp;
    if (!fila) return 0;

    p = fila->cabeca;
    while (p && p->dado.chave != chave)
        p = p->prox;
    if (!p) return 0;

    temp = p->dado;
    temp.prioridade = nova_prioridade;

    if (p->ant) p->ant->prox = p->prox;
    else fila->cabeca = p->prox;

    if (p->prox) p->prox->ant = p->ant;
    else fila->calda = p->ant;

    free(p);
    fila->tamanho--;

    return fila_inserir(fila, temp);
}

int fila_remover_item(FP *fila, int chave, Item *out) {
    No *p;
    if (!fila) return 0;

    p = fila->cabeca;
    while (p && p->dado.chave != chave)
        p = p->prox;
    if (!p) return 0;

    *out = p->dado;

    if (p->ant) p->ant->prox = p->prox;
    else fila->cabeca = p->prox;

    if (p->prox) p->prox->ant = p->ant;
    else fila->calda = p->ant;

    free(p);
    fila->tamanho--;
    return 1;
}

int fila_vazia(const FP *fila) {
    return !fila || fila->tamanho == 0;
}

int fila_tamanho(const FP *fila) {
    return fila ? fila->tamanho : 0;
}

void fila_listar(const FP *fila) {
    No *p;
    if (!fila) return;
    p = fila->cabeca;
    while (p) {
        printf("(item=%d, prioridade=%d) ", p->dado.chave, p->dado.prioridade);
        p = p->prox;
    }
    printf("\n");
}