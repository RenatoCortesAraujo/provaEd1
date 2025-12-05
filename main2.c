#include <stdio.h>
#include <stdlib.h>
#include "fp.h"
#include "qsort.h"

int main() {
    FP *fila = fila_criar();
    Item x;
    int i;

    printf("\n=====================================\n");
    printf("    TESTE DE FILA DE PRIORIDADE\n");
    printf("=====================================\n");

    // Inserir 6 itens
    Item itens[] = {
        {1, 20}, {2, 15}, {3, 40},
        {4, 30}, {5, 10}, {6, 25}
    };

    printf("\nInserindo itens na fila...\n");
    for (i = 0; i < 6; i++)
        fila_inserir(fila, itens[i]);

    printf("\nFila inicial:\n");
    fila_listar(fila);

    // Atualizar prioridade de um item
    printf("\n-------------------------------------\n");
    printf("Atualizando prioridade do item 2 -> 50\n");
    fila_atualizar(fila, 2, 50);

    printf("Fila apos atualizacao:\n");
    fila_listar(fila);

    // Remover do topo
    printf("\n-------------------------------------\n");
    printf("Removendo item de maior prioridade...\n");
    fila_remover_max(fila, &x);
    printf("Removido: chave=%d | prioridade=%d\n", x.chave, x.prioridade);

    printf("Fila restante:\n");
    fila_listar(fila);

    // Copiar itens para vetor
    int n = fila_tamanho(fila);
    Item *vet = (Item*)malloc(n * sizeof(Item));

    No *p = fila->cabeca;
    for (i = 0; i < n && p; i++, p = p->prox)
        vet[i] = p->dado;

    // Ordenar com QuickSort
    printf("\n=====================================\n");
    printf("         ORDENANDO COM QSORT\n");
    printf("=====================================\n");

    Metricas m;
    quick_sort(vet, n, PIVO_MEDIANA_DE_TRES, &m);

    printf("\nVetor ordenado:\n");
    for (i = 0; i < n; i++)
        printf("(chave=%d, prioridade=%d) ", vet[i].chave, vet[i].prioridade);
    printf("\n");

    printf("\nMetricas do QuickSort:\n");
    printf("  Comparacoes: %ld\n", m.comparacoes);
    printf("  Trocas:      %ld\n", m.trocas);

    printf("\n=====================================\n");
    printf("           FIM DO PROGRAMA\n");
    printf("=====================================\n\n");

    free(vet);
    fila_destruir(&fila);

    return 0;
}
