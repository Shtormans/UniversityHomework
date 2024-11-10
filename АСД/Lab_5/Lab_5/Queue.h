#pragma once

#include "Node.h"
#include <functional>

template<typename T>
class Queue
{
private:
	Node<T> m_first;
	Node<T>* m_last = nullptr;

	int m_length;

public:
	Queue()
	{

	}

	void Enqueue(T value)
	{
		Node<T>* node = new Node<T>(value);

		if (m_length > 0)
		{
			m_last->Next = node;
		}

		m_last = node;

		if (m_length == 0)
		{
			m_first.Next = m_last;
		}

		m_length++;
	}

	T Dequeue()
	{
		if (m_length == 0)
		{
			return NULL;
		}

		Node<T>* temp = m_first.Next->Next;
		T value = m_first.Next->Data;

		delete m_first.Next;

		m_first.Next = temp;

		m_length--;

		if (m_length == 0)
		{
			m_first.Next = nullptr;
			m_last = nullptr;
		}

		return value;
	}

	int IndexOf(T value)
	{
		int index = -1;
		int currentIndex = 0;

		Iterate([&value, &currentIndex, &index](T current)
			{
				if (current == value)
				{
					index = currentIndex;
				}

				currentIndex++;
			});

		return index;
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
		m_last = nullptr;
		m_length = 0;
	}

	void SwapFirstAndLast()
	{
		T temp = m_first.Next->Data;
		m_first.Next->Data = m_last->Data;
		m_last->Data = temp;
	}

	void Reverse()
	{
		Node<T>* head = nullptr;
		Node<T>* tail = nullptr;
		int length = m_length;

		Iterate([&head, &tail](T value)
			{
				head = new Node<T>(value, head);

				if (tail == nullptr)
				{
					tail = head;
				}
			});

		Clear();

		m_first.Next = head;
		m_last = tail;
		m_length = length;
	}
};

