#pragma once
#include <cstddef>

#include "Node.h"

template <typename T>
class Stack {
private:
    Node<T>* top;

public:
    Stack() : top(nullptr) {}

    void Push(T value) {
        Node<T>* node = new Node<T>(value);
        node->next = top;
        top = node;
    }

    T Pop() {
        if (IsEmpty())
        {
            return NULL;
        }

        Node<T>* temp = top;
        T value = temp->data;
        top = top->next;

        delete temp;

        return value;
    }

    T Peek() const {
        if (IsEmpty())
        {
            return NULL;
        }

        return top->data;
    }

    bool IsEmpty() const {
        return top == nullptr;
    }

    ~Stack() {
        while (!IsEmpty()) Pop();
    }
};
