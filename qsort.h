#ifndef QSORT_H
#define QSORT_H
#include "fp.h"

typedef enum { 
    PIVO_PRIMEIRO, 
    PIVO_ULTIMO, 
    PIVO_MEDIANA_DE_TRES,
    PIVO_RANDOM
} Estrategia;

typedef struct {
    long comparacoes;
    long trocas;
} Metricas;

void quick_sort(Item *v, int n, Estrategia e, Metricas *m);

#endif
