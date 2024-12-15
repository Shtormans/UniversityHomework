#pragma once

#include <iostream>
#include "HeapChunk.h"

class ChunksContainer
{
private:
	HeapChunk* _start;
	size_t _memorySize;


	HeapChunk* CreateChunk(size_t size, void* memory)
	{
		HeapChunk* chunk = static_cast<HeapChunk*>(memory);

		chunk->InUse = false;
		chunk->Size = size;
		chunk->Next = nullptr;
		chunk->SetMemory(memory);

		return chunk;
	}

	bool CanCreateChunk(size_t memorySize)
	{
		return memorySize > HeapChunk::GetFunctionalMemoryUsage();
	}

	void CreateFirstChunk(size_t size, void* memory)
	{
		HeapChunk* chunk = CreateChunk(size, memory);

		_memorySize = chunk->Size;
		_start = chunk;
	}

	void AddChunkAfter(HeapChunk* newChunk, HeapChunk* oldChunk)
	{
		newChunk->Next = oldChunk->Next;
		oldChunk->Next = newChunk;
	}

	void TruncateChunk(HeapChunk* chunk, size_t neededSize)
	{
		if (chunk->GetUnoccupiedMemorySize() == neededSize)
		{
			chunk->InUse = true;
			return;
		}

		size_t remainingSize = chunk->GetUnoccupiedMemorySize() - neededSize;
		if (!CanCreateChunk(remainingSize))
		{
			chunk->InUse = true;
			return;
		}

		void* remainingMemory = chunk->MemoryRegion + GetActualMemorySize(neededSize);
		HeapChunk* unusedChunk = CreateChunk(remainingSize, remainingMemory);

		AddChunkAfter(unusedChunk, chunk);

		chunk->Size = GetActualMemorySize(neededSize);
		chunk->InUse = true;
	}

	void TryCoalesceNearbyChunks(HeapChunk* chunk)
	{
		HeapChunk* previous = FindByNext(chunk);
		HeapChunk* next = chunk->Next;

		TryCoalesceChunks(chunk, next);
		TryCoalesceChunks(previous, chunk);
	}

	void TryCoalesceChunks(HeapChunk* previous, HeapChunk* next)
	{
		if (previous == nullptr || previous->InUse)
		{
			return;
		}

		if (next == nullptr || next->InUse)
		{
			return;
		}

		previous->Size += next->Size;
		previous->Next = next;

		previous->Next = next->Next;
	}

	HeapChunk* FindByMemoryRegion(const void* memoryRegion) const
	{
		HeapChunk* current = _start;

		while (current != nullptr)
		{
			if (current->GetUnoccupiedMemory() == memoryRegion)
			{
				return current;
			}

			current = current->Next;
		}

		return nullptr;
	}

	HeapChunk* FindByNext(const HeapChunk* chunk) const
	{
		HeapChunk* current = _start;

		while (current != nullptr)
		{
			if (current->Next == chunk)
			{
				return current;
			}

			current = current->Next;
		}

		return nullptr;
	}

	HeapChunk* FindSmallest(size_t size) const
	{
		HeapChunk* current = _start;
		HeapChunk* min = nullptr;

		while (current != nullptr)
		{
			if (current->InUse)
			{
				current = current->Next;
				continue;
			}

			if (current->GetUnoccupiedMemorySize() < size)
			{
				current = current->Next;
				continue;
			}

			if (min == nullptr)
			{
				min = current;
			}
			else if (current->Size < min->Size)
			{
				current = min;
			}

			current = current->Next;
		}

		return min;
	}

public:
	ChunksContainer() = default;

	ChunksContainer(size_t size, void* memory)
	{
		CreateFirstChunk(size, memory);
	}

	static size_t GetActualMemorySize(size_t size)
	{
		return HeapChunk::GetFunctionalMemoryUsage() + size;
	}

	void* GetFreeChunk(size_t size)
	{
		HeapChunk* chunk = FindSmallest(size);

		if (chunk == nullptr)
		{
			throw std::exception("No free chunks");
		}

		TruncateChunk(chunk, size);

		return chunk->GetUnoccupiedMemory();
	}

	void FreeChunk(const void* memory)
	{
		HeapChunk* chunk = FindByMemoryRegion(memory);

		if (chunk == nullptr)
		{
			throw std::exception("No such memory exists");
		}

		if (!chunk->InUse)
		{
			throw std::exception("This memory region is not occupied");
		}

		chunk->InUse = false;

		TryCoalesceNearbyChunks(chunk);
	}

	void DebugMemory() const
	{
		HeapChunk* current = _start;
		int i = 0;

		while (current != nullptr)
		{
			std::cout << "Item: " << i << '\n';
			std::cout << "In Use: " << (current->InUse ? "true" : "false") << '\n';
			std::cout << "Size: " << current->Size << '\n';
			std::cout << "Unoccupied size: " << current->GetUnoccupiedMemorySize() << '\n';
			std::cout << "Functional size: " << HeapChunk::GetFunctionalMemoryUsage() << '\n';
			std::cout << '\n';

			i++;
			current = current->Next;
		}

		std::cout << "\n";
	}
};

