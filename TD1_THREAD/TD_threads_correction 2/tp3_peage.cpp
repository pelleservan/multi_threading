// Utilise C++ 20

#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>
using namespace std;

const int num_cars = 10;
const int max_cars_at_toll = 2;
counting_semaphore sem_cars_at_toll(max_cars_at_toll);

void car(int id) {
    cout << "Car " << id << " has arrived at the toll.\n";
    sem_cars_at_toll.acquire();
    cout << "Car " << id << " is blocked at the toll.\n";
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Car " << id << " has left the toll.\n";
    sem_cars_at_toll.release();
}

int main() {
    thread cars[num_cars];
    for (int i = 0; i < num_cars; ++i) {
        cars[i] = thread(car, i);
    }
    for (int i = 0; i < num_cars; ++i) {
        cars[i].join();
    }
    return 0;
}