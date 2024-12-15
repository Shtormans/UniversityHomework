#include <fstream>
#include <sstream>
#include <string>

#include "Heap.h"

void LoadFromFile(const char* filename, Heap& heap);
void SaveToFile(const char* filename, const Heap& heap);

int main()
{
	Heap heap(1024);

	heap.Debug(std::cout);

	int* i = heap.Allocate<int>();

	char* ch = heap.Allocate<char>();

	const void* c = heap.Allocate<char[128]>();

	heap.Debug(std::cout);

	heap.Free(c);

	heap.Debug(std::cout);

	heap.Allocate<char[32]>();

	heap.Debug(std::cout);

	heap.Free(i);

	heap.Debug(std::cout);

	heap.Free(ch);

	heap.Debug(std::cout);

	heap.Allocate<char[9]>();

	heap.Debug(std::cout);

	std::cout << "\n\n\n\n\n\n";


	Heap heap2;
	LoadFromFile("test2.txt", heap2);
	SaveToFile("test.txt", heap2);
}

void SaveToFile(const char* filename, const Heap& heap)
{
	std::ofstream file(filename);

	if (file.is_open())
	{
		file << heap;
		file.close();
	}
}

void LoadFromFile(const char* filename, Heap& heap)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			iss >> heap;
		}
		file.close();
	}
	else
	{
		std::cerr << "Error: File not found." << '\n';
	}
}
