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
			cout << "Error. Exceeded the maximum number of threads" << endl << "Maximum number of threads = " << max << endl;
			return;
		}
		else if (numThreads < 1)
		{
			cout << "Error. The number of threads cannot be negative" << endl;
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


