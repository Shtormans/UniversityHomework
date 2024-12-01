#pragma once

#include "Node.h"
#include <functional>

template<typename T>
class LinkedList
{
private:
	Node<T> m_first;
	int m_length;

public:
	LinkedList()
	{

	}

	void PushStart(T value)
	{
		Insert(value, 0);
	}

	void Insert(T value, int index)
	{
		if (index > m_length)
		{
			index = m_length;
		}

		Node<T>* node = new Node<T>(value);

		int currentIndex = 0;
		Node<T>* currentNode = &m_first;

		while (currentIndex <= m_length)
		{
			if (currentIndex == index)
			{
				node->Next = currentNode->Next;
				currentNode->Next = node;

				break;
			}

			currentNode = currentNode->Next;
			currentIndex++;
		}

		m_length++;
	}

	void RemoveAt(int index)
	{
		int currentIndex = 0;
		Node<T>* currentNode = &m_first;

		while (currentIndex < m_length)
		{
			if (currentIndex == index)
			{
				Node<T>* nextNode = currentNode->Next->Next;

				delete currentNode->Next;

				currentNode->Next = nextNode;

				break;
			}

			currentNode = currentNode->Next;
			currentIndex++;
		}

		m_length--;
	}

	void RemoveEach(int value)
	{
		int currentIndex = 0;
		int deletions = 0;
		Node<T>* currentNode = &m_first;

		while (currentIndex < m_length)
		{
			if ((currentIndex + 1) % value == 0)
			{
				Node<T>* nextNode = currentNode->Next->Next;

				delete currentNode->Next;
				deletions++;

				currentNode->Next = nextNode;
			}
			else
			{
				currentNode = currentNode->Next;
			}

			currentIndex++;
		}

		m_length -= deletions;
	}

	void Move(int index, int movements)
	{
		int currentIndex = 0;
		Node<T>* currentNode = &m_first;

		T value;

		while (true)
		{
			if (currentIndex == index)
			{
				Node<T>* nextNode = currentNode->Next->Next;

				value = currentNode->Next->Data;
				delete currentNode->Next;

				currentNode->Next = nextNode;

				break;
			}

			currentNode = currentNode->Next;
			currentIndex++;
		}

		m_length--;

		int finalIndex = (currentIndex + movements) % (m_length + 1);

		Insert(value, finalIndex);
	}

	void Iterate(std::function<void(T)> action)
	{
		Node<T>* currentNode = m_first.Next;

		while (currentNode != nullptr)
		{
			action(currentNode->Data);

			currentNode = currentNode->Next;
		}
	}

	void Clear()
	{
		Node<T>* currentNode = m_first.Next;

		while (currentNode != nullptr)
		{
			Node<T>* previous = currentNode;

			currentNode = currentNode->Next;

			delete previous;
		}

		m_first.Next = nullptr;
		m_length = 0;
	}

	void Sort(std::function<int(T, T)> comparator)
	{
		bool unsorted = true;
		while (unsorted)
		{
			unsorted = false;

			Node<T>* currentNode = m_first.Next;

			while (currentNode->Next != nullptr)
			{
				if (comparator(currentNode->Data, currentNode->Next->Data) > 0)
				{
					T temp = currentNode->Data;
					currentNode->Data = currentNode->Next->Data;
					currentNode->Next->Data = temp;

					unsorted = true;
				}

				currentNode = currentNode->Next;
			}
		}
	}

	LinkedList<T> Copy()
	{
		LinkedList<T> copy;

		Node<T>* currentNode = m_first.Next;
		Node<T>* currentNodeCopy = &copy.m_first;

		while (currentNode != nullptr)
		{
			Node<T>* node = new Node<T>(currentNode->Data);

			currentNodeCopy->Next = node;
			currentNodeCopy = node;

			currentNode = currentNode->Next;
		}

		return copy;
	}

	static LinkedList<T> Concat(LinkedList<T>& first, LinkedList<T>& second)
	{
		LinkedList<T> copy;
		Node<T>* currentNodeCopy = &copy.m_first;

		Node<T>* currentNode = first.m_first.Next;
		while (currentNode != nullptr)
		{
			Node<T>* node = new Node<T>(currentNode->Data);

			currentNodeCopy->Next = node;
			currentNodeCopy = node;

			currentNode = currentNode->Next;
		}

		currentNode = second.m_first.Next;
		while (currentNode != nullptr)
		{
			Node<T>* node = new Node<T>(currentNode->Data);

			currentNodeCopy->Next = node;
			currentNodeCopy = node;

			currentNode = currentNode->Next;
		}

		return copy;
	}

	static LinkedList<T> Intersect(LinkedList<T>& first, LinkedList<T>& second)
	{
		LinkedList<T> copy = first.Copy();

		Node<T>* currentNode = &copy.m_first;

		while (currentNode->Next != nullptr)
		{
			T data = currentNode->Next->Data;
			bool exist = false;

			second.Iterate([data, &exist](T value)
				{
					if (value == data)
					{
						exist = true;
					}
				});

			if (!exist)
			{
				Node<T>* nextNode = currentNode->Next->Next;

				delete currentNode->Next;

				currentNode->Next = nextNode;
			}
			else
			{
				currentNode = currentNode->Next;
			}
		}

		return copy;
	}
};

