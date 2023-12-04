#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <semaphore>

struct myitem {
    int id;
    int value;
};

std::mutex mtx; // mutex pour protéger la liste
std::list<myitem> input; // liste d'éléments à traiter
std::list<myitem> output1; // liste d'éléments extraits par thread 1
std::list<myitem> output2; // liste d'éléments extraits par thread 2
int count = 0; // compteur pour vérifier quand tous les éléments ont été insérés
std::counting_semaphore sem(3);

void insert_items(int id) {
    while (true) {
        sem.acquire();
        mtx.lock();
        if (count >= 100000) { // tous les éléments ont été insérés
            mtx.unlock();
            sem.release();
            break;
        }
        if (input.size() < 10) { // la liste a moins de 10 éléments
            myitem item = { count, count + 1 };
            input.push_back(item);
            count++;
            std::cout << "Thread " << id << " inserted item " << item.id << std::endl;
        }
        mtx.unlock();
        sem.release();
    }
}

void extract_items(int id, std::list<myitem>& output) {
    while (true) {
        sem.acquire();
        mtx.lock();
        if (output.size() >= 100000) { // tous les éléments ont été extraits
            mtx.unlock();
            sem.release();
            break;
        }
        if (!input.empty()) { // la liste n'est pas vide
            myitem item = input.front();
            input.pop_front();
            output.push_back(item);
            std::cout << "Thread " << id << " extracted item " << item.id << std::endl;
        }
        mtx.unlock();
        sem.release();
    }
}

int main() {
    std::thread threads[6];
    for (int i = 0; i < 4; i++) {
        threads[i] = std::thread(insert_items, i);
    }
    threads[4] = std::thread(extract_items, 4, std::ref(output1));
    threads[5] = std::thread(extract_items, 5, std::ref(output2));
    for (int i = 0; i < 6; i++) {
        threads[i].join();
    }
    return 0;
}