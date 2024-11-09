#include <iostream>
#include "LinkedList.h";

LinkedList<int> _first;
LinkedList<int> _second;

void Run();

int ChooseAction();
void Add();
void AddWithIndex();
void Remove();
void RemoveEach();
void Move();
void Clear();
void ShowAll();
void Concat();
void Copy();
void Intersect();
void Clear();
void SortAsc();
void SortDesc();


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
			AddWithIndex();
			break;
		case 3:
			Remove();
			break;
		case 4:
			RemoveEach();
			break;
		case 5:
			Move();
			break;
		case 6:
			ShowAll();
			break;
		case 7:
			Concat();
			break;
		case 8:
			Intersect();
			break;
		case 9:
			Copy();
			break;
		case 10:
			Clear();
			break;
		case 11:
			SortAsc();
			break;
		case 12:
			SortDesc();
			break;
		}

		std::cout << "\n\n";
	}
}

int ChooseAction()
{
	std::cout << "Make an action:" << std::endl;
	std::cout << " 1 - Add" << std::endl;
	std::cout << " 2 - Add with index" << std::endl;
	std::cout << " 3 - Remove at" << std::endl;
	std::cout << " 4 - Remove each" << std::endl;
	std::cout << " 5 - Move" << std::endl;
	std::cout << " 6 - Show all" << std::endl;
	std::cout << " 7 - Concat" << std::endl;
	std::cout << " 8 - Intersect" << std::endl;
	std::cout << " 9 - Copy" << std::endl;
	std::cout << " 10 - Clear" << std::endl;
	std::cout << " 11 - Sort Asc" << std::endl;
	std::cout << " 12 - Sort Desc" << std::endl;

	int choice;
	std::cin >> choice;

	return choice;
}

void Add()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	int value;
	std::cout << "Value: ";
	std::cin >> value;

	if (list == 1)
	{
		_first.PushStart(value);
	}
	else
	{
		_second.PushStart(value);
	}
}

void AddWithIndex()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	int value;
	std::cout << "Value: ";
	std::cin >> value;

	int index;
	std::cout << "Index: ";
	std::cin >> index;

	if (list == 1)
	{
		_first.Insert(value, index);
	}
	else
	{
		_second.Insert(value, index);
	}
}

void Remove()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	int index;
	std::cout << "Index: ";
	std::cin >> index;


	if (list == 1)
	{
		_first.RemoveAt(index);
	}
	else
	{
		_second.RemoveAt(index);
	}
}

void RemoveEach()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	int index;
	std::cout << "Index: ";
	std::cin >> index;

	if (list == 1)
	{
		_first.RemoveEach(index);
	}
	else
	{
		_second.RemoveEach(index);
	}
}

void Move()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	int index;
	std::cout << "Index: ";
	std::cin >> index;

	int movements;
	std::cout << "Movements: ";
	std::cin >> movements;

	if (list == 1)
	{
		_first.Move(index, movements);
	}
	else
	{
		_second.Move(index, movements);
	}
}

void Clear()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	if (list == 1)
	{
		_first.Clear();
	}
	else
	{
		_second.Clear();
	}
}

void Show(LinkedList<int> list)
{
	list.Iterate([](int number)
		{
			std::cout << number << " ";
		});
}

void ShowAll()
{
	Show(_first);

	std::cout << std::endl;
	std::cout << std::endl;

	Show(_second);
}

void Copy()
{
	int list;
	std::cout << "List: ";
	std::cin >> list;

	if (list == 1)
	{
		Show(_first.Copy());
	}
	else
	{
		Show(_second.Copy());
	}
}

void Concat()
{
	Show(LinkedList<int>::Concat(_first, _second));
}

void Intersect()
{
	Show(LinkedList<int>::Intersect(_first, _second));
}

void SortAsc()
{
	auto function = [](int left, int right)
		{
			if (left > right)
			{
				return 1;
			}
			if (left == right)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		};

	int list;
	std::cout << "List: ";
	std::cin >> list;

	if (list == 1)
	{
		_first.Sort(function);
	}
	else
	{
		_second.Sort(function);
	}
}

void SortDesc()
{
	auto function = [](int left, int right)
		{
			if (left < right)
			{
				return 1;
			}
			if (left == right)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		};

	int list;
	std::cout << "List: ";
	std::cin >> list;

	if (list == 1)
	{
		_first.Sort(function);
	}
	else
	{
		_second.Sort(function);
	}
}