// compiler : g++ -std=c++11 -o TD_1.2 TD_1.2.cpp -lpthread

#include <iostream>
#include <thread>

// Fonction exécutée par les threads
void threadFunction(int threadID, int value) {
    std::cout << "Thread " << threadID << " en cours d'exécution.\n" << std::endl;

    for (int i = 0; i < 100000; i++) {
        value += i;
    }

    std::cout << "Value : " << value << std::endl;
}

int main() {

    int value = 0;

    // Créer trois threads
    std::thread thread1(threadFunction, 1, value);
    std::thread thread2(threadFunction, 2, value);
    std::thread thread3(threadFunction, 3, value);

    // Attendre que tous les threads aient terminé
    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "Tous les threads ont terminé." << std::endl;

    return 0;
}
