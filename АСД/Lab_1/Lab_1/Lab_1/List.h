#pragma once

#include<iostream>
#include <functional>


template<typename T>
class List
{
private:
	const int CapacityMultiplier = 2;
	static const int DefaultCapacity = 1;

	T* _items;
	int _capacity;
	int _length;
	bool _itemsAllocatedOnHeap;

	bool ValidateIndex(int index)
	{
		return index >= 0 && index < _length;
	}

	void ExpandItemsArray()
	{
		_capacity = _capacity * CapacityMultiplier;

		T* temp = new T[_capacity];
		std::copy(_items, _items + _length, temp);

		delete[] _items;

		_items = temp;
	}

	void DeleteItemsFromMemory()
	{
		for (int i = 0; i < _length; i++)
		{
			delete _items[i];
		}
	}

	void DeleteArrayFromMemory()
	{
		if (_itemsAllocatedOnHeap)
		{
			DeleteItemsFromMemory();
		}

		delete[] _items;
	}

public:
	List(bool itemsAllocatedOnHeap) : List(itemsAllocatedOnHeap, DefaultCapacity)
	{
	}

	List(bool itemsAllocatedOnHeap, int capacity)
	{
		_itemsAllocatedOnHeap = itemsAllocatedOnHeap;

		_capacity = capacity;
		_length = 0;

		_items = new T[_capacity];
	}

	~List()
	{
		DeleteArrayFromMemory();
	}

	int GetLength()
	{
		return _length;
	}

	int GetCapacity()
	{
		return _capacity;
	}

	void Add(T item)
	{
		if (_length == _capacity)
		{
			ExpandItemsArray();
		}

		_items[_length] = item;
		_length++;
	}

	bool TryRemove(T item, std::function<bool(T, T)> comparator)
	{
		if (_length == 0)
		{
			return false;
		}

		for (int i = 0; i < _length; i++)
		{
			if (comparator(_items[i], item))
			{
				RemoveAt(i);

				return true;
			}
		}

		return false;
	}

	void RemoveAt(int index)
	{
		if (!ValidateIndex(index))
		{
			return;
		}

		if (_itemsAllocatedOnHeap)
		{
			delete _items[index];
		}

		if (index != _length - 1)
		{
			std::copy(_items + index + 1, _items + _length, _items + index);
		}

		_length--;
	}

	void Clear()
	{
		DeleteItemsFromMemory();

		_length = 0;
	}

	List<T>* SelectWhere(std::function<bool(T)> predicate)
	{
		List<T>* result = new List<T>(_capacity);

		for (int i = 0; i < _length; i++)
		{
			T item = _items[i];

			if (predicate(item))
			{
				result->Add(item);
			}
		}

		return result;
	}

	T operator[](int index)
	{
		if (!ValidateIndex(index))
		{
			throw std::out_of_range("Index is out of range.");
		}

		T item = _items[index];
		return item;
	}
};

