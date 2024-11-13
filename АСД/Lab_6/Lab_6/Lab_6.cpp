#include <iostream>

void Run();
int ChooseAction();

void HashDivision();
void HashMultiplication();
void HashString();

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
			HashDivision();
			break;
		case 2:
			HashMultiplication();
			break;
		case 3:
			HashString();
			break;
		}

		std::cout << "\n\n";
	}
}

int ChooseAction()
{
	std::cout << "Make an action:" << std::endl;
	std::cout << " 1 - hash division" << std::endl;
	std::cout << " 2 - hash multiplication" << std::endl;
	std::cout << " 3 - hash string" << std::endl;

	int choice;
	std::cin >> choice;

	return choice;
}

void HashDivision() 
{
	int key;
	std::cout << "Key: ";
	std::cin >> key;

	const int M = 97;

	int hash = key % M;

	std::cout << "Hash: " << hash;
}

void HashMultiplication()
{
	int key;
	std::cout << "Key: ";
	std::cin >> key;

	const double A = 0.618033;
	const int M = 97;

	double fraction = (double)key * A;
	int hash = (int)((double)M * (fraction - (int)fraction));

	std::cout << "Hash: " << hash;
}

void HashString()
{
	std::string key;
	std::cout << "Key: ";
	std::cin >> key;

	const int A = 31;
	const int M = 97;
	int hash = 0;

	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + key[i] * (int)pow(A, i)) % M;
	}

	std::cout << "Hash: " << hash;
}