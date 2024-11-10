#pragma once

template<typename T>
struct Node
{
	T Data;
	Node<T>* Next;

	Node()
	{
		Data = 0;
		Next = nullptr;
	}

	Node(T data)
	{
		Data = data;
		Next = nullptr;
	}

	Node(T data, Node<T>* next)
	{
		Data = data;
		Next = next;
	}
};