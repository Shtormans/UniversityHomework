#include <iostream>

#include "Queue.h"

int main() {
    Queue<int> queue;

    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);

    std::cout << "Dequeue: " << queue.Dequeue() << "\n";  
    std::cout << "Peek: " << queue.Peek() << "\n";        

    queue.Enqueue(40);

    std::cout << "Dequeue: " << queue.Dequeue() << "\n";  
    std::cout << "Dequeue: " << queue.Dequeue() << "\n";  
    std::cout << "Dequeue: " << queue.Dequeue() << "\n";

    return 0;
}
