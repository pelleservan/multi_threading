#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 100;

    float *tableau = (float *)malloc(n * sizeof(float));
    
    for (int i = 0; i < n; i++) {
        tableau[i] = rand(); 
    }

    float somme_totale = 0;

#pragma omp parallel
    {
        float somme_partielle = 0;

#pragma omp for
        for (int i = 0; i < n; i++) {
            somme_partielle += tableau[i];
        }

#pragma omp critical
        {
            somme_totale += somme_partielle;
        }
    }
    printf("Somme totale : %f\n", somme_totale);
    
    free(tableau);

    return 0;
}
