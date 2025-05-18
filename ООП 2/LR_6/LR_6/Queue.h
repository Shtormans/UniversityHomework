#pragma once
#include "Stack.h"

template <typename T>
class Queue {
private:
    Stack<T> inStack;
    Stack<T> outStack;

    void TransferInToOut() {
        while (!inStack.IsEmpty()) {
            outStack.Push(inStack.Pop());
        }
    }

public:
    void Enqueue(T value) {
        inStack.Push(value);
    }

    T Dequeue() {
        if (IsEmpty())
        {
            return NULL;
        }

        if (outStack.IsEmpty())
        {
	        TransferInToOut();
        }

        return outStack.Pop();
    }

    T Peek() {
        if (IsEmpty())
        {
	        return NULL;
        }

        if (outStack.IsEmpty())
        {
	        TransferInToOut();
        }

        return outStack.Peek();
    }

    bool IsEmpty() {
        return inStack.IsEmpty() && outStack.IsEmpty();
    }
};
