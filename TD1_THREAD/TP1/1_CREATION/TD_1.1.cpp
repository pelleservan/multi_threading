// compiler : g++ -std=c++11 -o TD_1.1 TD_1.1.cpp -lpthread

#include <iostream>
#include <thread>

// Fonction exécutée par les threads
void threadFunction(int threadID) {
    std::cout << "Thread " << threadID << " en cours d'exécution.\n" << std::endl;
}

int main() {
    // Créer trois threads
    std::thread thread1(threadFunction, 1);
    std::thread thread2(threadFunction, 2);
    std::thread thread3(threadFunction, 3);

    // Attendre que tous les threads aient terminé
    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Tous les threads ont terminé." << std::endl;

    return 0;
}
