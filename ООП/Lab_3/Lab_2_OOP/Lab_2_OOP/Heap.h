#pragma once

#include <cstdlib>

#include "ChunksContainer.h"

#define MemorySize 1024

class Heap
{
private:
	ChunksContainer _chunks;

	static void* InternalAlloc(size_t size)
	{
		return malloc(size);
	}

public:
	Heap(const Heap& other)
	{
		_chunks = other._chunks;
	}

	Heap() : Heap(MemorySize)
	{

	}

	Heap(size_t memorySize)
	{
		size_t size = ChunksContainer::GetActualMemorySize(memorySize);
		void* memory = InternalAlloc(size);

		_chunks = ChunksContainer(size, memory);
	}

	void* Allocate(const size_t size)
	{
		return _chunks.GetFreeChunk(size);
	}

	template<typename T>
	T* Allocate()
	{
		return static_cast<T*>(Allocate(sizeof(T)));
	}

	void Free(const void* ptr)
	{
		_chunks.FreeChunk(ptr);
	}

	void Debug(std::ostream& out) const
	{
		_chunks.DebugMemory(out);
	}

	Heap& operator=(const Heap& other)
	{
		_chunks = other._chunks;
		return *this;
	}

	HeapChunk* operator[](const int index) const
	{
		return _chunks.GetByIndex(index);
	}

	friend std::ostream& operator<<(std::ostream& out, const Heap& heap)
	{
		heap.Debug(out);
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Heap& heap)
	{
		int size;
		in >> size;

		heap.Allocate(size);

		return in;
	}
};

