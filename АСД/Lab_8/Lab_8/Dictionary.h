#pragma once

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

		Node()
		{
			IsDeleted = true;
		}

		Node(TKey key, TValue value)
		{
			Key = key;
			Value = value;
			IsDeleted = false;
		}
	};

	int m_capacity;
	Node* m_table;
	std::function<int(TKey, int)> m_hashFunction;

	void Resize()
	{
		int oldCapacity = m_capacity;
		Node* oldTable = m_table;

		m_capacity *= CapacityMultiplier;
		m_table = new Node[m_capacity];

		for (int i = 0; i < oldCapacity; i++)
		{
			if (!oldTable[i].IsDeleted)
			{
				Add(oldTable[i].Key, oldTable[i].Value);
			}
		}

		for (int i = 0; i < m_capacity; i++)
		{
			bool b = m_table[i].IsDeleted;

			int v = 0;
		}

		delete[] oldTable;
	}

	Node* FindNode(TKey key)
	{
		int hash = m_hashFunction(key, m_capacity);

		int index = hash;
		int attempts = 0;

		while (m_table[index].IsDeleted || m_table[index].Key != key)
		{
			index = (index + 1) % m_capacity;
			attempts++;

			if (attempts >= m_capacity)
			{
				break;
			}
		}

		return &m_table[index];
	}

public:
	Dictionary(std::function<int(TKey, int)> hashFunction)
	{
		m_hashFunction = hashFunction;

		m_capacity = DefaultCapacity;
		m_table = new Node[DefaultCapacity];
	}

	void Add(TKey key, TValue value)
	{
		int hash = m_hashFunction(key, m_capacity);

		int index = hash;
		bool notFound = false;

		while (!m_table[index].IsDeleted)
		{
			index = (index + 1) % m_capacity;

			if (index == hash)
			{
				notFound = true;
				break;
			}
		}

		if (notFound)
		{
			Resize();
			Add(key, value);
		}
		else
		{
			m_table[index].Key = key;
			m_table[index].Value = value;
			m_table[index].IsDeleted = false;
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

			if (m_table[i].IsDeleted)
			{
				os << "empty";
			}
			else
			{
				os << m_table[i].Value;
			}

			os << "\t";

			if (i != m_capacity - 1)
			{
				os << std::endl;
			}
		}
	}
};

