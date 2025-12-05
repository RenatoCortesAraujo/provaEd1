#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"

// -------------------------------------------
// Troca dois itens
// -------------------------------------------
static void troca(Item *a, Item *b, Metricas *m) {
    Item tmp = *a;
    *a = *b;
    *b = tmp;
    m->trocas++;
}

// -------------------------------------------
// Mediana de três (PIVO_MEDIANA_DE_TRES)
// -------------------------------------------
static int mediana_de_tres(Item *v, int ini, int meio, int fim, Metricas *m) {
    int a = v[ini].chave;
    int b = v[meio].chave;
    int c = v[fim].chave;

    m->comparacoes += 3;

    if ((a > b) != (a > c)) return ini;
    if ((b > a) != (b > c)) return meio;
    return fim;
}

// -------------------------------------------
// Particionamento
// -------------------------------------------
static int particiona(Item *v, int ini, int fim, Estrategia e, Metricas *m) {
    int pivo_idx;
    int meio;
    Item pivo;
    int i, j;

    /* Escolha do pivô */
    if (e == PIVO_PRIMEIRO) {
        pivo_idx = ini;
    } else if (e == PIVO_ULTIMO) {
        pivo_idx = fim;
    } else if (e == PIVO_RANDOM) {
        pivo_idx = ini + rand() % (fim - ini + 1);
    } else { 
        /* PIVO_MEDIANA_DE_TRES */
        meio = (ini + fim) / 2;
        pivo_idx = mediana_de_tres(v, ini, meio, fim, m);
    }

    pivo = v[pivo_idx];
    troca(&v[pivo_idx], &v[fim], m);  // Move pivô para o fim

    i = ini;
    j = fim - 1;

    while (i <= j) {

        while (i <= j && v[i].chave <= pivo.chave) {
            m->comparacoes++;
            i++;
        }

        while (j >= i && v[j].chave > pivo.chave) {
            m->comparacoes++;
            j--;
        }

        if (i < j) {
            troca(&v[i], &v[j], m);
            i++;
            j--;
        }
    }

    troca(&v[i], &v[fim], m);

    return i;
}

// -------------------------------------------
// QuickSort recursivo
// -------------------------------------------
static void quick_rec(Item *v, int ini, int fim, Estrategia e, Metricas *m) {
    int q;
    if (ini >= fim) return;

    q = particiona(v, ini, fim, e, m);

    quick_rec(v, ini, q - 1, e, m);
    quick_rec(v, q + 1, fim, e, m);
}

// -------------------------------------------
// Função principal chamada pelo usuário
// -------------------------------------------
void quick_sort(Item *v, int n, Estrategia e, Metricas *m) {
    if (!v || n <= 1) return;

    m->comparacoes = 0;
    m->trocas = 0;

    /* Semente do random para PIVO_RANDOM */
    srand(12345);

    quick_rec(v, 0, n - 1, e, m);
}
