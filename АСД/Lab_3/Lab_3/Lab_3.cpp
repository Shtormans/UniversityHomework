#include <iostream>
#include "LinkedList.h";

void Run();

int ChooseAction();
void Show(LinkedList<int> list);

void Task1();
void Task2();
void Task3();
void Task4();


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
			Task1();
			break;
		case 2:
			Task2();
			break;
		case 3:
			Task3();
			break;
		case 4:
			Task4();
			break;
		}

		std::cout << "\n\n";
	}
}

int ChooseAction()
{
	std::cout << "Make an action:" << std::endl;
	std::cout << " 1 - First task" << std::endl;
	std::cout << " 2 - Second task" << std::endl;
	std::cout << " 3 - Third task" << std::endl;
	std::cout << " 4 - Fourth task" << std::endl;

	int choice;
	std::cin >> choice;

	return choice;
}

void Show(LinkedList<std::string> list, int length)
{
	int iterations = length;

	list.Iterate([&iterations](std::string number) -> bool
		{
			std::cout << number << " ";
			iterations--;

			return iterations > 0;
		});
}

void Task1()
{
	
}

void Task2()
{
	int n;
	std::cout << "N: ";
	std::cin >> n;

	int m;
	std::cout << "M: ";
	std::cin >> m;

	if (n == 1)
	{
		std::cout << 0 << std::endl;

		return;
	}

	LinkedList<bool> warriors;

	for (int i = 0; i < n; i++)
	{
		warriors.PushEnd(true);
	}

	int step = 0;

	warriors.Iterate([&n, &m, &step](bool* alive) -> bool
		{
			if (*alive)
			{
				step++;
			}

			if (step == m)
			{
				*alive = false;

				step = 0;
				n--;
			}

			return n > 1;
		});

	int index = 0;

	warriors.Iterate([&index](bool* alive) -> bool
		{
			if (*alive)
			{
				std::cout << index << std::endl;
			}

			index++;

			return !*alive;
		});

	warriors.Clear();
}

void Task3()
{
	int peopleAmount;
	std::cout << "People: ";
	std::cin >> peopleAmount;

	int n;
	std::cout << "N: ";
	std::cin >> n;

	int k;
	std::cout << "K: ";
	std::cin >> k;

	int t;
	std::cout << "T: ";
	std::cin >> t;

	int length = n;

	LinkedList<std::pair<std::string, bool>> people;
	LinkedList<std::string> gifts;
	LinkedList<std::string> winners;

	for (int i = 0; i < peopleAmount; i++)
	{
		std::string input;
		std::cin >> input;

		people.PushEnd(std::pair<std::string, bool>(input, true));
	}

	/*for (int i = 0; i < n; i++)
	{
		std::string input;
		std::cin >> input;

		gifts.PushEnd(input);
	}*/

	int step = 0;
	people.Iterate([&n, &k, &step, &winners](std::pair<std::string, bool>* person) -> bool
		{
			if ((*person).second)
			{
				step++;
			}

			if (step == k)
			{
				(*person).second = false;

				step = 0;
				n--;

				winners.PushEnd((*person).first);
			}

			return n > 0;
		});

	Show(winners, length);
}

void Task4()
{

}