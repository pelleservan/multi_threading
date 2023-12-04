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

    // Création de la mémoire partagée
    int sharedMemoryFd = shm_open(sharedMemoryName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (sharedMemoryFd == -1) {
        std::cerr << "Erreur lors de la création de la mémoire partagée." << std::endl;
        return EXIT_FAILURE;
    }

    // Définition de la taille de la mémoire partagée
    if (ftruncate(sharedMemoryFd, sharedMemorySize) == -1) {
        std::cerr << "Erreur lors de la définition de la taille de la mémoire partagée." << std::endl;
        shm_unlink(sharedMemoryName);
        return EXIT_FAILURE;
    }

    // Mappage de la mémoire partagée dans l'espace d'adressage du processus
    void* sharedMemory = mmap(nullptr, sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemoryFd, 0);
    if (sharedMemory == MAP_FAILED) {
        std::cerr << "Erreur lors du mappage de la mémoire partagée." << std::endl;
        close(sharedMemoryFd);
        shm_unlink(sharedMemoryName);
        return EXIT_FAILURE;
    }

    // Écriture dans la mémoire partagée
    {
        std::lock_guard<std::mutex> lock(mutex);
        std::string message = "Hello from Writer!";
        std::memcpy(sharedMemory, message.c_str(), message.size());
        std::cout << "Writer a écrit dans la mémoire partagée." << std::endl;
    }

    // Fermeture des ressources
    close(sharedMemoryFd);
    shm_unlink(sharedMemoryName);
    munmap(sharedMemory, sharedMemorySize);

    return EXIT_SUCCESS;
}
