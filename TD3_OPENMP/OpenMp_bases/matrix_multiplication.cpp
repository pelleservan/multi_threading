#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

void multiplyMatricesSingleThread(const std::vector<std::vector<int> >& A, const std::vector<std::vector<int> >& B, std::vector<std::vector<int> >& result) {
    int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiplyMatricesParallel(const std::vector<std::vector<int> >& A, const std::vector<std::vector<int> >& B, std::vector<std::vector<int> >& result, int numThreads) {
    int size = A.size();

#pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    const int size = 1024;
    const int numThreads = 4; // Change this to vary the number of threads

    // Initialize matrices
    std::vector<std::vector<int> > matrixA(size, std::vector<int>(size, 2));
    std::vector<std::vector<int> > matrixB(size, std::vector<int>(size, 3));
    std::vector<std::vector<int> > result(size, std::vector<int>(size, 0));

    // Measure time for single-threaded multiplication
    std::chrono::time_point<std::chrono::high_resolution_clock> startSingle = std::chrono::high_resolution_clock::now();
    multiplyMatricesSingleThread(matrixA, matrixB, result);
    std::chrono::time_point<std::chrono::high_resolution_clock> endSingle = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSingle = endSingle - startSingle;

    std::cout << "Single-threaded multiplication took " << elapsedSingle.count() << " seconds." << std::endl;

    // Measure time for multi-threaded multiplication
    std::chrono::time_point<std::chrono::high_resolution_clock> startParallel = std::chrono::high_resolution_clock::now();
    multiplyMatricesParallel(matrixA, matrixB, result, numThreads);
    std::chrono::time_point<std::chrono::high_resolution_clock> endParallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedParallel = endParallel - startParallel;

    std::cout << "Multi-threaded multiplication took " << elapsedParallel.count() << " seconds with " << numThreads << " threads." << std::endl;

    return 0;
}
