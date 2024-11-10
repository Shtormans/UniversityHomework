#include <iostream>
#include "Queue.h";

Queue<int> _first;

void Run();

int ChooseAction();
void Add();
void Remove();
void Clear();
void ShowAll();
void Swap();
void Reverse();
void Find();

int main()
{
	Run();
}


void Run()
{
	while (true)
	{
		int choice = ChooseAction();

		std::cout << "\n\n";

		switch (choice)
		{
		case 1:
			Add();
			break;
		case 2:
			Remove();
			break;
		case 3:
			ShowAll();
			break;
		case 4:
			Clear();
			break;
		case 5:
			Swap();
			break;
		case 6:
			Reverse();
			break;
		case 7:
			Find();
			break;
		}

		std::cout << "\n\n";
	}
}

int ChooseAction()
{
	std::cout << "Make an action:" << std::endl;
	std::cout << " 1 - Add" << std::endl;
	std::cout << " 2 - Remove" << std::endl;
	std::cout << " 3 - Show all" << std::endl;
	std::cout << " 4 - Clear" << std::endl;
	std::cout << " 5 - Swap" << std::endl;
	std::cout << " 6 - Reverse" << std::endl;
	std::cout << " 7 - Find" << std::endl;

	int choice;
	std::cin >> choice;

	return choice;
}

void Add()
{
	int value;
	std::cout << "Value: ";
	std::cin >> value;

	_first.Enqueue(value);
}

void Remove()
{
	_first.Dequeue();
}

void Clear()
{
	_first.Clear();
}

void Swap()
{
	_first.SwapFirstAndLast();
}

void Reverse()
{
	_first.Reverse();
}

void Find()
{
	int value;
	std::cout << "Value: ";
	std::cin >> value;

	std::cout << (_first.IndexOf(value) == -1 ? "False" : "True");
}

void ShowAll()
{
	_first.Iterate([](int number)
		{
			std::cout << number << " ";
		});
}