#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int size = 1000000;
    std::vector<int> array(size);

    // Initialisation du tableau avec des valeurs
    for (int i = 0; i < size; ++i) {
        array[i] = i + 1;
    }

    // Somme parallèle du tableau
    int sum = 0;
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }

    // Affichage du résultat
    std::cout << "La somme du tableau est : " << sum << std::endl;

    return 0;
}
