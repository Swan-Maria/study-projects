#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx1, mtx2;
void Print1()
{
	std::lock(mtx2, mtx1);
	std::lock_guard<std::mutex> lk1(mtx2, std::adopt_lock);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::lock_guard<std::mutex> lk2(mtx1, std::adopt_lock);
	for (int i = 0; i < 5; i++)
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << '*';
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Print2()
{
	std::lock(mtx1, mtx2);
	std::lock_guard<std::mutex> lg1(mtx1, std::adopt_lock);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::lock_guard<std::mutex> lg2(mtx2, std::adopt_lock);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << '#';
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
int main()
{
	std::jthread t1(Print1);
	std::jthread t2(Print2);
	return 0;
}
