#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <chrono>

using namespace std;

#define MAX_THREADS std::thread::hardware_concurrency()-1;


class threadpool {

private:
	class task {
	
	public:
		
		string status;
		function<void()>foo;
		task(function<void()>func)
		{
			foo = func;
			status = "In Queue";
		}

		void proc_stat()
		{
			status = "In Process";
		}

		void compl_stat()
		{
			status = "Completed";
		}

	};
	vector<thread> pool;
	vector<task> queue;
	mutex block;
	condition_variable thr;
	int numThreads;
	int coun;

public:

	threadpool(int num)
	{
		int max = MAX_THREADS
		numThreads = num;
		if (numThreads > max)
		{
			cout << "Error:: maximum number of threads reached" << endl << "Maximum number of threads = " << max << endl;
			return;
		}
		else if (numThreads < 1)
		{
			cout << "Error:: the number of threads cannot be negative" << endl;
			return;
		}

		for (int i = 0; i < numThreads; i++)
		{
			pool.emplace_back([this] {
				while (true)
				{
					for (int j = 0; j < queue.size(); j++)
					{

						if (queue[j].status == "In Queue")
						{
							bool thig = 1;
							block.lock();
							
							if (queue[j].status == "In Queue")
							{
								
								queue[j].proc_stat();
								block.unlock();
								thig = 0;
								queue[j].foo();
								queue[j].compl_stat();

							}
							if (thig)
							{
								block.unlock();
							}
						}
					}

					unique_lock<mutex> lock(block);
					thr.wait(lock, [this] {return !queue.empty(); });

					bool threadEnd = true;

					for (int i = 0; i < pool.size(); i++)
					{
						if (pool[i].get_id() == this_thread::get_id())
							threadEnd = false;
					}
					if (threadEnd)
						break;
				}
			});
			
		}

	}

	void add_task(function<void()> func)
	{
		unique_lock<mutex> lock(block);
		queue.push_back(task(func));
		thr.notify_one();

	}

	~threadpool()
	{
	/*	for (auto& t : pool)
		{
			t.detach();
		}
		pool.resize(0);
		thr.notify_all();
		this_thread::sleep_for(chrono::milliseconds(1000));*/
		int threads = pool.size();
		for (int i = threads; i > 0; i--)
		{
			thread tr = thread(move(pool.back()));
			pool.pop_back();
			thr.notify_one();
			tr.join();
		}
	}

};

//#include <mutex>
//#include <thread>
//#include <condition_variable>
//#include <memory>
//#include <string>
//#include <vector>
//#include <functional>
//
//
//
//class ThreadPool
//{
//private:
//	class Task
//	{
//	private:
//		std::string	          _statusWork;
//		std::function<void()> _job;
//	public:
//		Task(std::function<void()> job)
//		{
//			this->_job = job;
//			this->_statusWork = "inQueue";
//		}
//		void operator()() { _job(); };
//		std::string getStatusWork() { return this->_statusWork; };
//		void setStatusWork(std::string status) { this->_statusWork = status; };
//	};
//	std::mutex	                       _mutex;
//	std::condition_variable	           _condition;
//	std::vector<std::thread>           _threads;
//	std::vector<std::shared_ptr<Task>> _workerQueue;
//
//public:
//	auto push_task(std::function<void()> job)
//	{
//		std::unique_lock<std::mutex> lock(_mutex);
//		Task worker(job);
//		_workerQueue.push_back(std::make_shared<Task>(std::move(worker)));
//
//		_condition.notify_one();
//
//		return _workerQueue.back();
//	}
//
//	std::string getStatus(std::shared_ptr<Task> ptr) { return ptr->getStatusWork(); };
//
//	ThreadPool(unsigned int threadCount)
//	{
//		int MAX_THREADS = std::thread::hardware_concurrency() - 1;
//		if (threadCount > MAX_THREADS)
//			threadCount = MAX_THREADS;
//
//		for (int i = 0; i < threadCount; i++)
//		{
//			_threads.emplace_back([=] {
//				while (true)
//				{
//					for (int j = 0; j < _workerQueue.size(); j++)
//					{
//						auto Task = _workerQueue[j];
//
//						if (Task->getStatusWork() == "inQueue")
//						{
//							_mutex.lock();
//							(*Task).setStatusWork("inThreading");
//							_mutex.unlock();
//							(*Task)();
//							(*Task).setStatusWork("Completed");
//						}
//					}
//
//					std::unique_lock<std::mutex> lock(_mutex);
//					_condition.wait(lock, [this] {return !_workerQueue.empty(); });
//
//					bool threadEndWork = true;
//
//					for (auto iter : _workerQueue)
//					{
//						if (iter->getStatusWork() != "Completed")
//							threadEndWork = false;
//					}
//					if (threadEndWork)
//						break;
//				}
//			});
//		}
//	}
//	~ThreadPool()
//	{
//		for (auto& t : _threads)
//		{
//			if (t.joinable())
//				t.join();
//		}
//	}
//};
