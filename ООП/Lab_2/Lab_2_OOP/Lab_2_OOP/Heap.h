#pragma once

#include <cstdlib>

#include "ChunksContainer.h"

#define MemorySize 1024

class Heap
{
private:
	static Heap* _instance;

	ChunksContainer _chunks;

	Heap()
	{
		size_t size = ChunksContainer::GetActualMemorySize(MemorySize);
		void* memory = InternalAlloc(size);

		_chunks = ChunksContainer(size, memory);
	}

	static void* InternalAlloc(size_t size)
	{
		return malloc(size);
	}

	static void CreateInstanceIfNeeded()
	{
		if (_instance == nullptr)
		{
			_instance = new Heap();
		}
	}

public:
	static void* Allocate(const size_t size)
	{
		CreateInstanceIfNeeded();

		return _instance->_chunks.GetFreeChunk(size);
	}

	template<typename T>
	static T* Allocate()
	{
		return static_cast<T*>(Allocate(sizeof(T)));
	}

	static void Free(const void* ptr)
	{
		CreateInstanceIfNeeded();

		_instance->_chunks.FreeChunk(ptr);
	}

	static void Debug()
	{
		CreateInstanceIfNeeded();

		_instance->_chunks.DebugMemory();
	}
};

