#include <iostream>
#include <thread>
#include <vector>

void helloThread(int threadNum) {
    std::cout << "Hello thread " << threadNum << std::endl;
}

int main() {

    const int numThreads = 3;
    
    std::vector<std::thread> threads;
    
    for (int i = 1; i <= numThreads; ++i) {
        threads.push_back(std::thread(helloThread, i));
    }
    
    for (auto &t : threads) {
        t.join();
    }

    return 0;
}
