#include <atomic>
#include <thread>
#include <iostream>

class Spinlock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
        
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

Spinlock lock1;
int counter = 0;

void worker() {
    for (int i = 0; i < 1000000; i++) {
        lock1.lock();   
        counter++;         
        lock1.unlock();
    }
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    std::cout << "Counter = " << counter << "\n";
}
