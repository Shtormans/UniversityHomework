#include "Heap.h"

int main()
{
	Heap::Debug();

	int* i = Heap::Allocate<int>();

	char* ch = Heap::Allocate<char>();

	const void* c = Heap::Allocate<char[128]>();

	Heap::Debug();

	Heap::Free(c);

	Heap::Debug();

	c = Heap::Allocate<char[32]>();

	Heap::Debug();

	Heap::Free(i);

	Heap::Debug();

	Heap::Free(ch);

	Heap::Debug();

	c = Heap::Allocate<char[9]>();

	Heap::Debug();
}
