#include <iostream>
#include "Dictionary.h";


void Run();

int ChooseAction();
void Add();
void Remove();
void Find();
void Output();

int GetHashCode(int, int);

Dictionary<int, int> _dictionary(GetHashCode);

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
			Find();
			break;
		case 4:
			Output();
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
	std::cout << " 3 - Find" << std::endl;
	std::cout << " 4 - Output" << std::endl;

	int choice;
	std::cin >> choice;

	return choice;
}

void Add()
{
	int key;
	std::cout << "Key: ";
	std::cin >> key;

	int value;
	std::cout << "Value: ";
	std::cin >> value;

	_dictionary.Add(key, value);
}

void Remove()
{
	int key;
	std::cout << "Key: ";
	std::cin >> key;

	_dictionary.Remove(key);
}

void Find()
{
	int key;
	std::cout << "Key: ";
	std::cin >> key;

	std::cout << _dictionary.Find(key);
}

void Output()
{
	_dictionary.Print(std::cout);
}

int GetHashCode(int key, int M)
{
	const double A = 0.618033;

	double fraction = (double)key * A;
	int hash = (int)((double)M * (fraction - (int)fraction));

	return hash;
}