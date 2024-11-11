#include <iostream>
#include "LinkedList.h";

void Task();

int main()
{
	Task();
}

void Task()
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
	LinkedList<std::pair<std::string, bool>> gifts;
	LinkedList<std::string> winners;

	std::cout << "People:" << std::endl;

	for (int i = 0; i < peopleAmount; i++)
	{
		std::string input;
		std::cin >> input;

		people.PushEnd(std::pair<std::string, bool>(input, true));
	}

	std::cout << "Gifts:" << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::string input;
		std::cin >> input;

		gifts.PushEnd(std::pair<std::string, bool>(input, true));
	}

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

	std::cout << "Result:" << std::endl;

	LinkedList<std::string>::Iterator iterator = winners.GetIterator();
	n = length;
	step = 0;

	gifts.Iterate([&n, &t, &step, &winners, &iterator](std::pair<std::string, bool>* gift) -> bool
		{
			if ((*gift).second)
			{
				step++;
			}

			if (step == t)
			{
				(*gift).second = false;

				step = 0;
				n--;

				std::cout << iterator.GetCurrent() << "\t" << (*gift).first << std::endl;
				iterator.MoveNext();
			}

			return n > 0;
		});
}