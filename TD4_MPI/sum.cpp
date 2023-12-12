#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    const int array_size = 1000000;
    const int chunk_size = array_size / world_size;

    // Initialisez le tableau sur chaque processus avec des valeurs différentes
    std::vector<float> local_array(chunk_size);
    for (int i = 0; i < chunk_size; ++i) {
        local_array[i] = world_rank * chunk_size + i;
    }

    // Effectuez la somme partielle sur chaque processus
    float local_sum = 0;
    for (int i = 0; i < chunk_size; ++i) {
        local_sum += local_array[i];
    }

    // Utilisez MPI_Reduce pour calculer la somme totale
    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    std::cout << "Process " << world_rank << " out of " << world_size << " processes local sum " << local_sum << "." << std::endl;

    return 0;
}