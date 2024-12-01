#pragma once

#include <iostream>
#include <functional>

#define DefaultCapacity 3
#define CapacityMultiplier 2

template<typename TKey, typename TValue>
class Dictionary
{
private:
	struct Node
	{
		TKey Key;
		TValue Value;
		bool IsDeleted;
		Node* Next;

		Node(TKey key, TValue value)
		{
			Key = key;
			Value = value;

			IsDeleted = false;
			Next = nullptr;
		}
	};

	int m_capacity;
	Node** m_table;
	std::function<int(TKey, int)> m_hashFunction;

	Node* FindNode(TKey key)
	{
		int hash = m_hashFunction(key, m_capacity);

		Node* current = m_table[hash];
		while (current->IsDeleted || current->Key != key)
		{
			current = current->Next;
		}

		return current;
	}

public:
	Dictionary(std::function<int(TKey, int)> hashFunction)
	{
		m_hashFunction = hashFunction;

		m_capacity = DefaultCapacity;
		m_table = new Node * [DefaultCapacity];

		for (int i = 0; i < m_capacity; i++)
		{
			m_table[i] = nullptr;
		}
	}

	void Add(TKey key, TValue value)
	{
		int hash = m_hashFunction(key, m_capacity);

		Node* current = m_table[hash];

		if (current == nullptr)
		{
			m_table[hash] = new Node(key, value);
			return;
		}

		if (current->IsDeleted)
		{
			m_table[hash]->Key = key;
			m_table[hash]->Value = value;
			m_table[hash]->IsDeleted = false;

			return;
		}

		while (current->Next != nullptr && current->Next->IsDeleted)
		{
			current = current->Next;
		}

		if (current->Next == nullptr)
		{
			current->Next = new Node(key, value);
		}
		else
		{
			current->Next->Key = key;
			current->Next->Value = value;
			current->Next->IsDeleted = false;
		}
	}

	void Remove(TKey key)
	{
		FindNode(key)->IsDeleted = true;
	}

	TValue Find(TKey key)
	{
		return FindNode(key)->Value;
	}

	void Print(std::ostream& os)
	{
		for (int i = 0; i < m_capacity; i++)
		{
			os << i << ": ";

			Node* current = m_table[i];

			while (current != nullptr)
			{
				if (current->IsDeleted)
				{
					os << "deleted";
				}
				else
				{
					os << current->Value;
				}

				os << "\t";

				current = current->Next;
			}

			if (i != m_capacity - 1)
			{
				os << std::endl;
			}

		}
	}
};

