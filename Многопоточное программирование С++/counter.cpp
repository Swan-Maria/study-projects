#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <vector>

int threadCount = 10;
int iterations = 1000;

std::atomic<int> counter = 0;

int main()
{
	auto increment = []()
		{
			for (int i = 0; i < iterations; i++)
			{
				counter++;
			}
		};

	{
		std::vector<std::jthread> threads;
		for (int i = 0; i < threadCount; i++)
		{
			threads.emplace_back(increment);
		}
	}

	std::cout<<counter<<std::endl;

	return 0;
}