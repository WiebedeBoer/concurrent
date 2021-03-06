// concurrent6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//The thread pool pattern
//A thread pool is a group of pre - instantiated, idle worker threads which stand ready to be given work.
//These are preferred over instantiating new threads for each task when there is a large number of short tasks to be done,
//rather than a small number of long ones.
//This prevents having to incur the overhead of creating a thread a large number of times.

//The file threadpool.cpp implements such a threadpool.
//However, the worker threads in this thread pool suffer from the busy - wait problem.

//Study the program and change it(using std::condition_variable) 
//so that worker threads no longer busy - wait for new tasks to arrive.

// threadpool.cpp
// Compile with:
// g++ -std=c++11 -pthread threadpool.cpp -o threadpool

#include "pch.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <deque>

class ThreadPool; // forward declare

class Worker {
public:
	Worker(ThreadPool &s) : pool(s) { }
	void operator()();
private:
	ThreadPool &pool;
};

class ThreadPool {
public:
	ThreadPool(size_t threads);
	template<class F> void enqueue(F f);
	~ThreadPool();
private:
	friend class Worker;

	std::vector<std::thread> workers;
	std::deque<std::function<void()>> tasks;

	std::mutex queue_mutex;
	bool stop;
};

void Worker::operator()()
{
	std::function<void()> task;
	while (true)
	{
		std::unique_lock<std::mutex> locker(pool.queue_mutex);
		if (pool.stop) return;
		if (!pool.tasks.empty())
		{
			task = pool.tasks.front();
			pool.tasks.pop_front();
			locker.unlock();
			task();
		}
		else {
			locker.unlock();
		}
	}
}

ThreadPool::ThreadPool(size_t threads) : stop(false)
{
	for (size_t i = 0; i < threads; ++i)
		workers.push_back(std::thread(Worker(*this)));
}

ThreadPool::~ThreadPool()
{
	stop = true; // stop all threads

	for (auto &thread : workers)
		thread.join();
}

template<class F>
void ThreadPool::enqueue(F f)
{
	std::unique_lock<std::mutex> lock(queue_mutex);
	tasks.push_back(std::function<void()>(f));
}

int main()
{
	ThreadPool pool(4);

	// queue a bunch of "work items"
	for (int i = 0; i < 8; ++i)
		pool.enqueue([i]() { std::cout << "Hello from work item " << i << std::endl; });

	// wait for keypress to give worker threads the opportunity to finish tasks
	std::cin.ignore();

	return 0;
}