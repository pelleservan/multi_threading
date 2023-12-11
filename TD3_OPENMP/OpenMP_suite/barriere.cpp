#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 10000

void print_array(float array[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%f ", array[i]);
    }
    printf("\n");
}

int main() {
    int i;
    float array[ARRAY_SIZE];
    
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand();
    }

    for (int i = 1; i <100; i+=10) {

        int num_threads = i;

        omp_set_num_threads(num_threads);

        double start_parallel = omp_get_wtime();
        #pragma omp parallel for
        for (i = 0; i < ARRAY_SIZE; ++i) {
            array[i] *= 2;
        }
        double end_parallel = omp_get_wtime();

        #pragma omp barrier

        printf("Array size : %d | ", ARRAY_SIZE);
        printf("Num thread : %d |", num_threads);
        printf("Run time : %f s\n", end_parallel - start_parallel);

    }

    return 0;
}
