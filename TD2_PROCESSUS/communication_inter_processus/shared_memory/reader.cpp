#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mutex>

int main() {
    const char* sharedMemoryName = "/my_shared_memory";
    const int sharedMemorySize = 4096;

    // Création du mutex
    std::mutex mutex;

    // Ouverture de la mémoire partagée
    int sharedMemoryFd = shm_open(sharedMemoryName, O_RDWR, S_IRUSR | S_IWUSR);
    if (sharedMemoryFd == -1) {
        std::cerr << "Erreur lors de l'ouverture de la mémoire partagée." << std::endl;
        return EXIT_FAILURE;
    }

    // Mappage de la mémoire partagée dans l'espace d'adressage du processus
    void* sharedMemory = mmap(nullptr, sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFd, 0);
    if (sharedMemory == MAP_FAILED) {
        std::cerr << "Erreur lors du mappage de la mémoire partagée." << std::endl;
        close(sharedMemoryFd);
        return EXIT_FAILURE;
    }

    // Lecture depuis la mémoire partagée
    {
        std::lock_guard<std::mutex> lock(mutex);
        char buffer[256];
        std::memcpy(buffer, sharedMemory, sizeof(buffer));
        std::cout << "Reader a lu depuis la mémoire partagée : " << buffer << std::endl;
    }

    // Fermeture des ressources
    close(sharedMemoryFd);
    munmap(sharedMemory, sharedMemorySize);

    return EXIT_SUCCESS;
}
