#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::queue<int> buffer;          
const unsigned int MAX_SIZE = 5; 
std::mutex mtx;                  
std::condition_variable cv_producer;
std::condition_variable cv_consumer;
bool finished = false;

void producer(int id) {
    for (int i = 1; i <= 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        cv_producer.wait(lock, [] { return buffer.size() < MAX_SIZE; });

        int value = id * 100 + i;
        buffer.push(value);
        std::cout << "producer [" << id << "] add: " << value << std::endl;

        lock.unlock();
        cv_consumer.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        cv_consumer.wait(lock, [] { return !buffer.empty() || finished; });

        while (!buffer.empty()) {
            int value = buffer.front();
            buffer.pop();
            std::cout << "consumer [" << id << "] get: " << value << std::endl;
            cv_producer.notify_one();
        }

        if (finished)
        {
            break;
        }
    }
}

int main() {
    std::thread prod1(producer, 1);
    std::thread prod2(producer, 5);
    std::thread cons1(consumer, 9);

    prod1.join();
    prod2.join();

    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv_consumer.notify_all();

    cons1.join();

    std::cout << "Program finished.\n";
    return 0;
}