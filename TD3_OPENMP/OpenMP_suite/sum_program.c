#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int i;
    int array[ARRAY_SIZE];
    int sum_sequential = 0, sum_parallel = 0;
    
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    // Séquentielle
    double start_sequential = omp_get_wtime();
    for (i = 0; i < ARRAY_SIZE; ++i) {
        sum_sequential += array[i];
    }
    double end_sequential = omp_get_wtime();

    // Parallèle
    double start_parallel = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_parallel)
    for (i = 0; i < ARRAY_SIZE; ++i) {
        sum_parallel += array[i];
    }
    double end_parallel = omp_get_wtime();
    
    printf("Somme séquentielle: %d\n", sum_sequential);
    printf("Somme parallèle: %d\n", sum_parallel);
    
    printf("Temps d'exécution séquentiel: %f secondes\n", end_sequential - start_sequential);
    printf("Temps d'exécution parallèle: %f secondes\n", end_parallel - start_parallel);

    return 0;
}
