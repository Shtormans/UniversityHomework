#pragma once

template<typename TKey, typename TValue>
class Dictionary
{
private:
	struct Node 
	{
		TKey Key;
		TValue Value;
		bool IsDeleted;

		Node(TKey key, TValue value)
		{
			Key = key;
			Value = value;
			IsDeleted = false;
		}
	};

	int m_capacity;
	Node** m_table;
};

