#include "0_Utils.h"

void print_element(int n)
{
	std::cout << n << " ";
}

void add_value(int& n, int value)
{
	n += value;
}

int main()
{
	std::vector<int> numbers = { 10,20,10,30,40,10,50 };
	custom_utils::for_each(numbers.begin(), numbers.end(), print_element);
	std::cout << "\n\n";
	//std::cout << custom_utils::count(numbers.begin(), numbers.end(), 10) << "\n\n";
	//std::cout << custom_utils::count_if(numbers.begin(), numbers.end(), [](int n) {return n % 3 == 0;}) << "\n\n";
	custom_utils::replace(numbers.begin(), numbers.end(), 10, 9);
	custom_utils::for_each(numbers.begin(), numbers.end(), print_element);
	std::cout << "\n\n";

	custom_utils::replace_if(numbers.begin(), numbers.end(), [](int n) {return n % 4 == 0;}, 0);
	custom_utils::for_each(numbers.begin(), numbers.end(), print_element);
	std::cout << "\n\n";


	/*std::vector<int> source(10);
	std::iota(source.begin(), source.end(), 1);

	std::vector<int> destination(10);

	custom_utils::copy(source.begin(), source.end(), destination.begin());
	custom_utils::for_each(destination.begin(), destination.end(), print_element);
	std::cout << "\n\n";

	std::vector<int> destination_if;

	custom_utils::copy_if(source.begin(), source.end(), std::back_inserter(destination_if), [](int n) {return n % 2 == 0;});
	custom_utils::for_each(destination_if.begin(), destination_if.end(), print_element);
	std::cout << "\n\n";*/

	/*std::vector<int> numbers = { 10,20,30,40,50 };
	custom_utils::for_each(numbers.begin(), numbers.end(), print_element);
	std::cout << "\n\n";


	std::vector<char> numbers_next(5);
	custom_utils::for_each(numbers_next.begin(), numbers_next.end(), print_element);
	std::cout << "\n\n";
	std::iota(numbers_next.begin(), numbers_next.end(), 'A');
	custom_utils::for_each(numbers_next.begin(), numbers_next.end(), [](char& s) {s += 10;});
	std::cout << "\n\n";*/

	return 0;
}