#pragma once
struct HeapChunk
{
	size_t Size;
	bool InUse;
	char* MemoryRegion;

	HeapChunk* Next;

	char* GetUnoccupiedMemory() const
	{
		return MemoryRegion + sizeof(HeapChunk);
	}

	size_t GetUnoccupiedMemorySize() const
	{
		return Size - sizeof(HeapChunk);
	}

	void SetMemory(void* memory)
	{
		MemoryRegion = static_cast<char*>(memory);
	}

	static size_t GetFunctionalMemoryUsage()
	{
		return sizeof(HeapChunk);
	}
};

