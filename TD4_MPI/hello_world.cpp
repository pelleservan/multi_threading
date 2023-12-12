#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    std::cout << "Hello world from process " << world_rank << " out of " << world_size << " processes." << std::endl;

    MPI_Finalize();

    return 0;
}
