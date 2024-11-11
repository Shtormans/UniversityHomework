#pragma once

#include "Node.h"
#include <functional>

template<typename T>
class LinkedList
{
private:
	Node<T>* m_first;
	Node<T>* m_last;

public:
	LinkedList()
	{
		m_first = nullptr;
		m_last = nullptr;
	}

	void PushEnd(T value)
	{
		Node<T>* node = new Node<T>(value);

		if (m_first == nullptr)
		{
			m_first = node;
			m_last = node;
		}
		else
		{
			m_last->Next = node;
			m_last = node;
		}

		node->Next = m_first;
	}

	void Iterate(std::function<bool(T)> action)
	{
		Node<T>* currentNode = m_first;

		while (action(currentNode->Data))
		{
			currentNode = currentNode->Next;
		}
	}

	void Iterate(std::function<bool(T*)> action)
	{
		Node<T>* currentNode = m_first;

		while (action(&currentNode->Data))
		{
			currentNode = currentNode->Next;
		}
	}

	void Clear()
	{
		Node<T>* currentNode = m_first;

		while (currentNode != nullptr)
		{
			Node<T>* previous = currentNode;

			currentNode = currentNode->Next;

			delete previous;
		}

		m_first = nullptr;
		m_last = nullptr;
	}

	class Iterator
	{
	private:
		Node<T>* m_current;

	public:
		Iterator(LinkedList<T>* list)
		{
			m_current = list->m_first;
		}

		T GetCurrent()
		{
			return m_current->Data;
		}

		bool MoveNext()
		{
			if (m_current->Next == nullptr)
			{
				return false;
			}

			m_current = m_current->Next;
			return true;
		}
	};

	Iterator GetIterator()
	{
		return Iterator(this);
	}
};

