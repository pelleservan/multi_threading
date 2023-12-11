// lunch => cclang++ -Xpreprocessor -fopenmp -I$(brew --prefix libomp)/include -L$(brew --prefix libomp)/lib -o hello_world hello_world.cpp -lomp  

#include <stdio.h>
#include <omp.h>

int main() {
   
    #pragma omp parallel num_threads(4)
    {
        
        printf("Hello world from thread %d\n", omp_get_thread_num());
    }

    return 0;
}
