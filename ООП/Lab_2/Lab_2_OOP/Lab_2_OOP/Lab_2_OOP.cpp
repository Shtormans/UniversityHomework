#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Heap.h"

void load_from_file(const char* filename, Heap& heap);
void save_to_file(const char* filename, const Heap& heap);
void run();
void allocate();
void free();

Heap heap_(1024);
std::vector<std::pair<int, void*>> allocatedMemory;

int main()
{
	run();
}

void run()
{
	while (true)
	{
		std::cout << "1 - Allocate memory\n";
		std::cout << "2 - Free memory\n";
		std::cout << "3 - Save to file\n";
		std::cout << "4 - Load from file\n";
		std::cout << "5 - Debug\n";

		int num;
		std::cin >> num;

		std::cout << "\n";

		switch (num)
		{
		case 1:
			allocate();
			break;
		case 2:
			free();
			break;
		case 3:
			save_to_file("test1.txt", heap_);
			break;
		case 4:
			load_from_file("test1.txt", heap_);
			break;
		case 5:
			heap_.Debug(std::cout);
			break;
		default: 
			break;
		}

		std::cout << "\n\n";
	}
}

void allocate()
{
	std::cout << "Amount to allocate: ";
	int amount;
	std::cin >> amount;

	void* ptr = heap_.Allocate(amount);

	allocatedMemory.emplace_back(amount, ptr);
}

void free()
{
	std::cout << "Select memory region\n";
	for (int i = 0; i < allocatedMemory.size(); i++)
	{
		std::cout << i << ": " << allocatedMemory[i].first << "\n";
	}

	int index;
	std::cin >> index;

	heap_.Free(allocatedMemory[index].second);

	allocatedMemory.erase(allocatedMemory.begin() + index);
}

void save_to_file(const char* filename, const Heap& heap)
{
	std::ofstream file(filename);

	if (file.is_open())
	{
		file << heap;
		file.close();
	}
}

void load_from_file(const char* filename, Heap& heap)
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
