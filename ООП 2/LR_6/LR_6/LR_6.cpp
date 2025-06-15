#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "Queue.h"

Queue<int> queue;
std::mutex queueMutex;

void Producer() {
	for (int i = 1; i <= 5; ++i) 
	{
		{
			std::lock_guard<std::mutex> lock(queueMutex);

			std::cout << "[Producer] Enqueue: " << i * 10 << "\n";
			queue.Enqueue(i * 10);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Consumer() {
	for (int i = 0; i < 5; ++i) 
	{
		while (true) 
		{
			{
				std::lock_guard<std::mutex> lock(queueMutex);

				if (!queue.IsEmpty()) 
				{
					std::cout << "[Consumer] Dequeue: " << queue.Dequeue() << "\n";
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

int main() {
	std::thread producerThread(Producer);
	std::thread consumerThread(Consumer);

	producerThread.join();
	consumerThread.join();

	std::cout << "All operations completed.\n";
	return 0;
}
