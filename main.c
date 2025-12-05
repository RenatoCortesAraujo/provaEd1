#include <stdio.h>
#include <stdlib.h>
#include "fp.h"
#include "qsort.h"

int main(void) {
    int i;
    FP *fila = fila_criar();
    if (!fila) return 1;

    Item itens[] = {
        {1, 20}, {2, 15}, {3, 40},
        {4, 30}, {5, 10}, {6, 25}
    };

    for (i = 0; i < 6; i++)
        fila_inserir(fila, itens[i]);

    printf("\nFila inicial:");
    fila_listar(fila);

    // Atualizar prioridade
    fila_atualizar(fila, 2, 50);
    printf("\nApos atualizar item 2 -> prioridade 50:");
    fila_listar(fila);

    // Remover topo
    Item out;
    fila_remover_max(fila, &out);
    printf("Removido do topo: chave=%d, prioridade=%d", out.chave, out.prioridade);
    fila_listar(fila);

    // Copiar itens para vetor
    int n = fila_tamanho(fila);
    Item *vet = (Item*)malloc(n * sizeof(Item));
    No *p = fila->cabeca;
    for (i = 0; i < n && p; i++, p = p->prox)
        vet[i] = p->dado;

    // Ordenar com quick sort (mediana de tres)
    Metricas m;
    quick_sort(vet, n, PIVO_MEDIANA_DE_TRES, &m);

    printf("\nVetor ordenado (Quick Sort):\n");
    for (i = 0; i < n; i++)
        printf("(chave=%d, prioridade=%d) \n", vet[i].chave, vet[i].prioridade);
    printf("Comparacoes: %ld | Trocas: %ld\n", m.comparacoes, m.trocas);

    free(vet);
    fila_destruir(&fila);
    return 0;
}
