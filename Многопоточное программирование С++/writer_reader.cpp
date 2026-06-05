#include <iostream>
#include <thread>
#include <shared_mutex>
int shared_data = 0;
std::shared_mutex shared_mtx;
void reader() {
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		std::shared_lock<std::shared_mutex> lock(shared_mtx);
		std::cout << "Reader " << std::this_thread::get_id() << " read data: " << shared_data << std::endl;
	}
}
void writer(int value) {
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::unique_lock<std::shared_mutex> lock(shared_mtx);
		std::cout << "--- Writer " << std::this_thread::get_id() << " started writing ---" << std::endl;
		shared_data = value;
		std::cout << "--- Writer " << std::this_thread::get_id() << " finished writing. New value: " << shared_data << " ---" << std::endl;
	}
}
int main() {
	std::jthread reader1(reader);
	std::jthread reader2(reader);
	std::jthread writer1(writer, 10);
	std::jthread reader3(reader);
	std::jthread writer2(writer, 20);
}
