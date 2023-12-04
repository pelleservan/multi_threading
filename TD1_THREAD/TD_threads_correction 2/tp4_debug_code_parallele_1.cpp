#include <cstdlib>
#include <iostream>
#include <atomic>
#include <thread>
#include <array> // Include manquant
void thread_func(int* val)
{
	for (int i = 0; i < 1000000; i++)
	{
		(*val)++;
	}
}
int main(int argc, char** argv)
{
	std::array<std::thread, 4> th;
	size_t nb = th.size();
	int val = 0;
	for (size_t i = 0; i < nb; i++)
	{
		th[i] = std::thread(thread_func, &val);
	}
	for (size_t i = 0; i < nb; i++)
	{
			/* wait threads to terminate */
			th[i].join();
	}
	std::cout << "val = ";
	std::cout << val << std::endl;
	std::cout << "Exit program" << std::endl;
	return EXIT_SUCCESS;
}