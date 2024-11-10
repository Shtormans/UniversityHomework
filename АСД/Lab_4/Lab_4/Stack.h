#pragma once

#include "Node.h"
#include <functional>

template<typename T>
class Stack
{
private:
	Node<T> m_first;
	Node<T>* m_last = nullptr;

	int m_length;

public:
	Stack()
	{

	}

	void Push(T value)
	{
		Node<T>* node = new Node<T>(value, m_first.Next);

		m_first.Next = node;

		if (m_length == 0)
		{
			m_last = m_first.Next;
		}

		m_length++;
	}

	T Pop()
	{
		if (m_length == 0)
		{
			return NULL;
		}

		Node<T>* temp = m_first.Next;
		T value = temp->Data;

		m_first.Next = m_first.Next->Next;

		delete temp;

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
		Stack<T> temp;

		Iterate([&temp](T value)
			{
				temp.Push(value);
			});

		Clear();

		m_first = temp.m_first;
		m_last = temp.m_last;
		m_length = temp.m_length;
	}
};

