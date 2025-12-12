/*
Умова: Розробити симулятор системи обробки фінансових замовлень.
Система має три основні етапи:
1. Генерація (Producer)
2. Обробка (Consumer)
3. Фінальний Звіт (Reporting)
*/
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono> 

using namespace std;

// Структура замовлення
struct Order
{
	int id;
	int quantity;
	double price;
};

// Глобальні ресурси
queue<Order> order_queue;
mutex queue_mtx;
condition_variable cv_order;

atomic<int> processed_count(0);
const int TOTAL_ORDERS_TO_PROCESS = 15;

atomic<bool> producers_finished(false);

// Загальний дохід
double final_total_revenue (0.0);
mutex revenue_mtx;

void producer(int client_id, int orders_to_generate)
{
	cout << "Client [" << client_id << "] creating " << orders_to_generate << " orders.\n";

	for (int i = 0; i < orders_to_generate; ++i)
	{
		Order order{
			client_id * 100 + i,
			(rand() % 10) + 1,
			(rand() % 1000) / 10.0 + 5.0
		};

		{
			lock_guard<mutex> lock(queue_mtx);
			order_queue.push(order);
			cout << "Client [" << client_id << "] added order #" << order.id << "\n";
		}

		cv_order.notify_one();
		this_thread::sleep_for(chrono::milliseconds(rand() % 20 + 50));
	}
}

void expensive_processing()
{
	this_thread::sleep_for(chrono::milliseconds(80 + rand() % 40));
}

void consumer(int worker_id)
{
    while (true)
    {
        Order current;

        {
            unique_lock<mutex> lock(queue_mtx);

            cv_order.wait(lock, [] {
                return !order_queue.empty() || producers_finished.load();
                });

            if (order_queue.empty() && producers_finished.load(std::memory_order_acquire))
                break;

            current = order_queue.front();
            order_queue.pop();
        }

        expensive_processing();

        double revenue = current.quantity * current.price;

        {
            lock_guard<mutex> lock(revenue_mtx);
            final_total_revenue += revenue;
        }

        int done = processed_count.fetch_add(1) + 1;

        cout << "Worker [" << worker_id << "] processed order #"
            << current.id << "| revenue: " << revenue
            << "| total processed: " << done << "\n";

        if (done >= TOTAL_ORDERS_TO_PROCESS)
            return;    
    }
}

int main()
{
    srand(time(NULL));

    thread p1(producer, 1, 7);
    thread p2(producer, 2, 8);

    thread c1(consumer, 1);
    thread c2(consumer, 2);
    thread c3(consumer, 3);

    p1.join();
    p2.join();

    producers_finished.store(true, memory_order_release);
    cv_order.notify_all();

    c1.join();
    c2.join();
    c3.join();

    cout << "\n==================== FINAL REPORT ====================\n";
    cout << "Total processed orders: " << processed_count.load() << "\n";
    cout << "Final total revenue: " << final_total_revenue << "\n";
    cout << "=======================================================\n";

    return 0;
}
