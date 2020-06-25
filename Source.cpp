#include "thread.h"

void task_1(int a, int b)
{
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "Mult: " << a * b << endl;
}

void task_2()
{
	this_thread::sleep_for(chrono::milliseconds(2000));
	cout << "Text: " << "AAAAAAAAA" << endl;
}

int main()
{
	threadpool th(3);
	th.add_task([&]() {task_1(4, 5); });
	th.add_task([&]() {task_1(1, 5); });
	th.add_task([&]() {task_2(); });
	th.add_task([&]() {task_1(2, 5); });
	th.add_task([&]() {task_2(); });
	th.add_task([&]() {task_1(2, 5); });
	th.add_task([&]() {task_2(); });
	system("pause");
	return 0;
}


//#include <iostream>
//#include <functional>
//#include<vector>
//#include<mutex>
//#include<string>
//#include<chrono>
//#include<atomic>
//
//using namespace std;
//
//struct Task//+
//{
//	function<void()>task;
//	string status;
//	decltype(thread().get_id()) ID;
//	Task(const function<void()>& task, const string& status)
//	{
//		this->task = task;
//		this->status = status;
//	}
//};
//
//class Thread_Pool
//{
//public:
//	const vector<string>status = { "ADDED","FINISHING","THREADED","DONE","CANCELED" };
//
//	Thread_Pool()//+
//	{
//		this->max_thread_number = 0;
//		this->stopped = false;
//	}
//
//	~Thread_Pool()
//	{
//		cancel();
//	}
//
//	const Task& add(const function<void()>& task)//+
//	{
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		this->tasks.emplace_back(Task(task, this->status[0]));
//		const Task& ref = this->tasks[this->tasks.size() - 1];
//		return ref;
//	}
//
//	void start(const unsigned int& number = thread::hardware_concurrency())//+
//	{
//		if (number < 1)
//		{
//			cout << "Number of threads can`t be less than 1!\n";
//			return;
//		}
//		set_thread_number(number);
//		for (int i = 0; i < this->max_thread_number; i++)
//		{
//			vector<Task>& v_ref = this->tasks;
//			mutex& mtx = this->_vec_mtx;
//			pool.push_back(thread([this, &v_ref, &mtx]()
//				{
//					while (!stopped)
//					{
//						for (int j = 0; j < v_ref.size(); j++)
//						{
//							unique_lock<mutex>LOCK(this->_vec_mtx);
//							if (v_ref[j].status == this->status[0])
//							{
//								v_ref[j].status = this->status[2];
//								LOCK.unlock();
//								v_ref[j].task();
//								LOCK.lock();
//								tasks[j].status = this->status[3];
//							}
//						}
//					}
//				}));
//		}
//		for (auto& ref : this->pool)
//			ref.join();
//		while (true)
//		{
//			string ch;
//			cout << "Do you want to finish your tasks?(Y/N)\n";
//			cin >> ch;
//			if (ch == "Y")
//			{
//				unique_lock<mutex>LOCK(this->_vec_mtx);
//				for (int i = 0; i < tasks.size(); i++)
//					if (tasks[i].status == status[0]) tasks[i].status = status[1];
//				LOCK.unlock();
//				finish();
//				break;
//			}
//			else if (!cin.good())
//			{
//				cin.clear();
//				cin.ignore(10000, '\n');
//				cout << "Invalid symbols found!\n";
//			}
//			else
//			{
//				cancel();
//				break;
//			}
//		}
//	}
//
//	void cancel()//+
//	{
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		for (int i = 0; i < this->tasks.size(); i++)
//			if (this->tasks[i].status != this->status[3])this->tasks[i].status = this->status[4];
//	}
//
//	void stop()//+
//	{
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		this->stopped = true;
//	}
//
//	vector<string> get_statuses()
//	{
//		vector<string>G;
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		for (int i = 0; i < this->tasks.size(); i++)
//			G.push_back(this->tasks[i].status);
//		return G;
//	}
//private:
//
//	atomic<bool>stopped;
//
//	mutex _vec_mtx;
//
//	vector<Task>tasks;
//
//	vector<thread> pool;
//
//	unsigned int max_thread_number;
//
//	void set_thread_number(const unsigned int& number = thread::hardware_concurrency());//+
//
//	void finish()
//	{
//		for (int i = 0; i < this->max_thread_number; i++)
//		{
//			vector<Task>& v_ref = this->tasks;
//			mutex& mtx = this->_vec_mtx;
//			pool[i] = thread([this, &v_ref, &mtx]()
//				{
//					for (int j = 0; j < v_ref.size(); j++)
//					{
//						unique_lock<mutex>LOCK(this->_vec_mtx);
//						if (v_ref[j].status == this->status[1])
//						{
//							v_ref[j].status = this->status[2];
//							LOCK.unlock();
//							v_ref[j].task();
//							LOCK.lock();
//							tasks[j].status = this->status[3];
//						}
//					}
//				});
//		}
//		for (auto& ref : this->pool)
//			ref.join();
//		cout << "Finished\n";
//		cancel();
//	}
//};
//
//void Thread_Pool::set_thread_number(const unsigned int& number)//+
//{
//	int max = thread::hardware_concurrency();
//	if (number >= max)
//	{
//		while (true)
//		{
//			cout << "WARNING! ALL " << max << " CPU`S WILL BE USED! DO YOU WANT TO CONTINUE?(Y/N)\n";
//			if (cin.get() == 'Y')
//			{
//				this->max_thread_number = max;
//				break;
//			}
//			else if (!cin.good())
//			{
//				cin.clear();
//				cin.ignore(10000, '\n');
//				cout << "Invalid symbols found!\n";
//			}
//			else
//			{
//				this->max_thread_number = number;
//				break;
//			}
//		}
//	}
//	else
//	{
//		this->max_thread_number = number;
//	}
//	cout << "SET COMPLETED\n";
//}
//
//int f1()
//{
//	//this_thread::sleep_for(chrono::seconds(6));
//	for (int i = 0; i < 1000; i++)
//		cout << 2;
//	cout << "F1\n";
//	return 10;
//}
//
//int f2(int a)
//{
//	//this_thread::sleep_for(chrono::seconds(3));
//	for (int i = 0; i < 1000; i++)
//		cout << 1;
//	cout << " F2\n";
//	return a;
//}
//
//
//int main()
//{
//	int a;
//	Thread_Pool tp;
//	function<void()>ff1 = []() {f1(); };
//	function<void()>ff2 = [&]() {a = f2(10); };
//	for (int i = 0; i < 10; i++)
//	{
//		tp.add(ff1);
//		tp.add(ff2);
//		tp.add(ff1);
//		tp.add(ff2);
//		tp.add(ff1);
//		tp.add(ff2);
//	}
//	tp.add(function<void()>([&tp]() {tp.stop(); }));
//	//thread t(&Thread_Pool::start, &tp,4);
//	tp.start();
//	tp.add(function<void()>([]() {f1(); }));
//	tp.add(function<void()>([]() {f2(5); }));
//	//tp.stop();
//	vector<string>v = tp.get_statuses();
//	//t.join();
//
//	cout << a << endl;
//	for (auto au : v)
//		cout << au << endl;
//	system("pause");
//	return 0;
//}


//#include <thread>
//#include <mutex>
//#include <functional>
//#include <vector>
//#include <queue>
//#include <string>
//#include <condition_variable>
//#include <iostream>
//#include <chrono>
//#include <time.h>
//using namespace std;
//
//#define MAX_THREADS std::thread::hardware_concurrency() - 1;
//
//class Th_pool {
//public:
//	void resize(int newCount) {
//		int tmp = MAX_THREADS;
//		if (newCount <= 0 || newCount > tmp) {
//
//
//		}
//		else {
//			if (newCount > numThreads) {
//				uint8_t tmp = numThreads;
//				numThreads = newCount;
//				Pool.resize(numThreads);
//				Th_id.resize(numThreads);
//				for (int i = tmp; i != numThreads; ++i) {
//
//					Pool.emplace_back(move(thread(&Th_pool::thread_while, this)));
//					Th_id.emplace_back(Pool.back().get_id());
//					Pool.back().detach();
//				}
//			}
//			else {
//
//				numThreads = newCount;
//				Pool.resize(newCount);
//				Th_id.resize(newCount);
//			}
//		}
//	}
//
//private:
//
//	class task {
//	private:
//		function<void(int)> func;
//		int info;
//		string stat;
//		bool trig = 1;
//	public:
//		~task() {}
//		task(function<void(int)> ff, int inf) {
//			func = ff;
//			info = inf;
//			stat = "in the queue";
//
//		}
//		void performed_f() {
//			trig = 0;
//			stat = "performed";
//			trig = 1;
//		}
//		void completed_f() {
//			trig = 0;
//			stat = "completed";
//			trig = 1;
//		}
//		void execute() {
//
//			func(info);
//
//
//
//		}
//		string statys() {
//			while (!trig) {
//
//			}
//			return stat;
//		}
//	};
//	int numThreads;
//	vector<thread> Pool;
//	vector<thread::id> Th_id;
//	vector<shared_ptr<task>> taskQueue;
//	condition_variable thread_c;
//	mutex taskMutex;
//
//	void thread_while() {
//		srand(0);
//		while (true) {
//
//			for (int i = 0; i < taskQueue.size(); i++) {
//				shared_ptr<task> cc = taskQueue[i];
//				string rr = this->statys(cc);
//
//				if (rr == "in the queue") {
//					//shared_ptr<task> cc = taskQueue[i];
//					taskMutex.lock();
//					(*cc).performed_f();
//					taskMutex.unlock();
//					(*cc).execute();
//
//					(*cc).completed_f();
//
//					//for (int j = 0; j < taskQueue.size(); j++) {
//
//					//    if (taskQueue[j] == cc) {
//					//        taskQueue.erase(taskQueue.begin() + j);
//					//    }
//					//}
//
//
//				}
//
//			}
//
//			unique_lock<mutex> lock(taskMutex);
//			thread_c.wait(lock, [this] {return !taskQueue.empty(); });
//
//			bool tr = 1;
//
//			for (int i = 0; i < Th_id.size(); i++) {
//
//				if (Th_id[i] == this_thread::get_id()) {
//					tr = 0;
//					break;
//				}
//
//			}
//			if (tr) {
//				break;
//			}
//		}
//	}
//public:
//	Th_pool(int th_size) : numThreads(th_size) {
//		int tmp = MAX_THREADS;
//		if (numThreads > tmp) {
//			numThreads = tmp;
//		}
//		Pool.reserve(numThreads);
//		Th_id.reserve(numThreads);
//		for (int i = 0; i != numThreads; ++i) {
//
//			Pool.emplace_back(thread(&Th_pool::thread_while, this));
//			Th_id.emplace_back(Pool.back().get_id());
//			Pool.back().detach();
//		}
//
//
//
//	}
//	shared_ptr<task> push_task(function<void(int)> func, int info) {
//		unique_lock<mutex> lock(taskMutex);
//		task tt(func, info);
//
//		taskQueue.push_back(std::make_shared<task>(std::move(tt)));
//		thread_c.notify_one();
//		return taskQueue.back();
//	}
//	string statys(shared_ptr<task> tas) {
//
//		string rr = (*tas).statys();
//
//		return rr;
//	}
//
//	~Th_pool() {
//		this_thread::sleep_for(chrono::milliseconds(1000));
//		while (this->statys(taskQueue[taskQueue.size() - 1]) != "completed") {
//
//		}
//		Th_id.resize(0);
//		this_thread::sleep_for(chrono::milliseconds(1000));
//
//	}
//};
//void rrr(int r) {
//	this_thread::sleep_for(chrono::milliseconds(100));
//	cout << r;
//
//}
//
//
//int main() {
//	Th_pool pool(6);
//
//	auto tt = pool.push_task(rrr, 1);
//	cout << pool.statys(tt) << endl;
//
//	thread th([&] {
//		for (int i = 0; i < 100; i++) {
//			pool.push_task(rrr, 2);
//			pool.push_task(rrr, 3);
//			pool.push_task(rrr, 4);
//			pool.push_task(rrr, 5);
//		}
//		this_thread::sleep_for(chrono::milliseconds(100));
//		for (int i = 0; i < 100; i++) {
//			pool.push_task(rrr, 2);
//			pool.push_task(rrr, 3);
//			pool.push_task(rrr, 4);
//			pool.push_task(rrr, 5);
//		}
//		});
//	th.detach();
//
//
//	auto ttt = pool.push_task(rrr, 1);
//
//	auto data = pool.push_task(rrr, 2);
//	while (pool.statys(data) != "completed") {
//
//
//	}
//	cout << pool.statys(data) << endl;
//	system("pause");
//	return 0;
//}


//#include <iostream>
//#include <thread>
//#include <functional>
//#include <vector>
//#include <mutex>
//#include <string>
//#include <queue>
//#include "time.h"
//#include <atomic>
//
//using namespace std;
//
//class Task
//{
//public:
//
//	Task(const function<void(int)>& added_task, int& num)
//	{
//		task = added_task;
//		data = num;
//		status = "added_to_list";
//	}
//
//	int get_data()
//	{
//		return data;
//	}
//
//	function<void(int)> task;
//	string status;
//
//private:
//
//	int data;
//};
//
//class thread_pull
//{
//private:
//
//	char ans;
//
//	int thread_num;
//
//	vector<thread> thr_list;
//
//	mutex mtx;
//
//	atomic<bool> paused;
//
//	vector<Task> tasks;
//
//	void cancel()
//	{
//		unique_lock<mutex> ul(mtx);
//		for (int i = 0; i < tasks.size(); i++)
//		{
//			if (tasks[i].status != "done")
//				tasks[i].status = "canceled";
//		}
//	}
//
//	void check_ans()
//	{
//		for (;;)
//		{
//			cout << "Finish remaining tasks?(y/n)\n";
//			cin >> ans;
//			if (ans == 'y')
//			{
//				unique_lock<mutex> ul(mtx);
//				for (int i = 0; i < tasks.size(); i++)
//				{
//					if (tasks[i].status == "added_to_list")
//						tasks[i].status = "going to finish";
//				}
//				ul.unlock();
//				finish();
//				break;
//			}
//			else if (ans == 'n')
//			{
//				cancel();
//				break;
//			}
//			else
//				cout << "Incorrect symbol!\n";
//		}
//	}
//
//	void finish()
//	{
//		paused = false;
//		for (int i = 0; i < thread_num; i++)
//		{
//			thr_list[i] = thread([this]()
//				{
//					for (int j = 0; j < tasks.size(); j++)
//					{
//						unique_lock<mutex> ul(mtx);
//						if (tasks[j].status == "going to finish")
//						{
//							tasks[j].status = "added_to_thread";
//							ul.unlock();
//							tasks[j].task(tasks[j].get_data());
//							ul.lock();
//							tasks[j].status = "done";
//						}
//					}
//				});
//		}
//		for (auto& ref : thr_list)
//			ref.join();
//
//		cancel();
//	}
//
//public:
//
//
//	thread_pull(const int& num)
//	{
//		paused = false;
//
//		if (num < 1 || num > std::thread::hardware_concurrency() - 1)
//		{
//			cout << "Incorrect thread number! \n";
//			cout << "Thread number needs to be from 1 to " << std::thread::hardware_concurrency() - 1 << endl;
//			exit(0);
//		}
//		else
//			thread_num = num;
//	}
//
//	void get_status()
//	{
//		unique_lock<mutex> ul(mtx);
//		for (int i = 0; i < tasks.size(); i++)
//		{
//			cout << "Status of task #" << i + 1 << "   is: " << tasks[i].status << endl;
//		}
//	}
//
//	void add_func(function<void(int)>func, int smth)
//	{
//		unique_lock<mutex> ul(mtx);
//		tasks.push_back(Task(func, smth));
//	}
//
//	void start()
//	{
//		for (int i = 0; i < thread_num; i++)
//		{
//			thr_list.push_back(thread([this]()
//			{
//
//					for (int j = 0; j < tasks.size(); j++)
//					{
//						if (!paused)
//						{
//							unique_lock<mutex> u_l(mtx);
//							if (tasks[j].status == "added_to_list")
//							{
//								tasks[j].status = "added_to_thread";
//								u_l.unlock();
//								tasks[j].task(tasks[j].get_data());
//								u_l.lock();
//								tasks[j].status = "done";
//							}
//						}
//						else break;
//					}
//
//			}));
//		}
//		for (auto& ref : thr_list)
//			ref.join();
//
//		check_ans();
//	}
//
//	void cancel_all()
//	{
//		unique_lock<mutex> ul(mtx);
//		paused = true;
//	}
//
//	void pause()
//	{
//		unique_lock<mutex> ul(mtx);
//		int a = 0;
//		tasks.push_back(Task([this](int d) {this->cancel_all(); }, a));
//	}
//
//};
//
//void test_func(int data)
//{
//	this_thread::sleep_for(chrono::milliseconds(500));
//
//	for (int i = 0; i < 1000; i++)
//		data += i;
//
//	cout << "Func ended successfully with data = " << data << endl;
//}
//
//void test_func_2(int data)
//{
//	cout << "Func 2 started!\n";
//	for (int i = 20; i < 120; i += 20)
//	{
//		this_thread::sleep_for(chrono::milliseconds(500));
//		data -= i;
//
//	}
//	cout << "Func 2 ended successfully!" << data << endl;
//}
//
//int main()
//{
//	int a = 1;
//
//	thread_pull th(3);									     //указать количество потоков	
//
//	for (int i = 10; i < 500; i += 10)
//	{
//		th.add_func(test_func, i);
//	}
//
//	//th.add_func([&th, &a](int d) {th.cancel_all(); }, 1);  	
//	th.pause();												//отменяет впереди стоящие таски
//	th.add_func(test_func, 120);
//	th.add_func(test_func, 130);
//	th.add_func(test_func, 140);
//	th.add_func(test_func, 150);
//	th.add_func(test_func, 160);
//	th.get_status();
//
//	//th.cancel_all();									    //отменяет все таски
//
//	th.add_func(test_func, 5000);
//	th.add_func(test_func, 5000);
//	th.add_func(test_func, 5000);
//
//	th.start();
//
//	th.add_func(test_func, 41);
//	th.add_func(test_func, 42);
//	th.add_func(test_func, 43);
//
//	th.get_status();
//
//
//	system("pause");
//	return 0;
//}



//#include "thread.h"
//#include <iostream>
//#include <chrono>
//
//void func1()
//{
//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
//	std::cout << "A";
//}
//
//void func2()
//{
//	std::this_thread::sleep_for(std::chrono::milliseconds(200));
//	std::cout << "O";
//}
//
//
//int main()
//{
//	ThreadPool pool(2);
//
//	std::thread thr([&] {
//		for (int i = 0; i < 10; i++) {
//			pool.push_task(func1);
//			pool.push_task(func2);
//		}
//		});
//	thr.detach();
//
//	auto test = pool.push_task(func1);
//	std::cout << test->getStatusWork() << std::endl;
//
//	system("pause");
//}

//#include <iostream>
//#include <thread>
//#include <vector>
//#include <string>
//#include <functional>
//#include <future>
//#include <chrono>
//
//using namespace std;
//
//struct task
//{
//	string stat;
//	function<void()> func;
//	task(string status, function<void()> func)
//	{
//		this->stat = status;
//		this->func = func;
//	}
//};
//
//class threadpool
//{
//public:
//	threadpool()
//	{
//		flag = true;
//		thcount = 0;
//	}
//	~threadpool()
//	{
//		for (int i = 0; i < threads.size(); i++)
//		{
//			threads[i].join();
//		}
//	}
//	void addTask(function<void()> func)
//	{
//		lock_guard<mutex> mtx(blocker);
//		queue.push_back(task(statuses[0], func));
//	}
//	void run(int threadnum = thread::hardware_concurrency() - 1)
//	{
//		thcount += threadnum;
//		if (thcount > thread::hardware_concurrency() - 1)
//		{
//			cout << "Error:: maximum number of threads reached" << endl;
//			return;
//		}
//		else if (threadnum < 1)
//		{
//			cout << "Error:: the number of threads cannot be negative" << endl;
//			return;
//		}
//		for (int i = 0; i < threadnum; i++)
//		{
//			threads.push_back(thread([this]()
//				{
//					while (flag)
//					{
//						for (int i = 0; i < queue.size(); i++)
//						{
//
//							if (queue[i].stat == statuses[0])
//							{
//								queue[i].stat = statuses[1];
//								queue[i].func();
//								queue[i].stat = statuses[2];
//								break;
//							}
//						}
//					}
//				}));
//		}
//	}
//	void end()
//	{
//		flag = false;
//	}
//	string getStat(int index)
//	{
//		if (index <= 0)
//		{
//			return "Error";
//		}
//		else if (index > queue.size())
//		{
//			return "Error";
//		}
//		else
//		{
//			return queue[index - 1].stat;
//		}
//	}
//
//private:
//	vector<task> queue;
//	const vector<string> statuses = { "Waiting","In process","Complete" };
//	mutex blocker;
//	vector<thread> threads;
//	bool flag;
//	int thcount;
//};
//
//
//
//
//
//
//void test(int x)
//{
//	this_thread::sleep_for(chrono::milliseconds(4000));
//	cout << "This is cool tekst: " << x << endl;
//}
//
//void test1(int x, int y)
//{
//	this_thread::sleep_for(chrono::milliseconds(1500));
//	cout << "Tekst: " << x * y << endl;
//}
//
//string test2()
//{
//	this_thread::sleep_for(chrono::milliseconds(1000));
//	cout << "1111111111111111" << endl;
//	return "1111111111111111";
//}
//
//int main()
//{
//	threadpool tp;
//	tp.addTask([&]() {test1(7, 9); });
//	tp.addTask([&]() {test2(); });
//	tp.addTask([&]() {test2(); });
//	tp.addTask([&]() {test(8); });
//	tp.addTask([&]() {test2(); });
//	tp.addTask([&]() {test2(); });
//
//	tp.addTask([&]() {test2(); });
//	tp.addTask([&]() {tp.end(); });
//	cout << tp.getStat(4) << endl;
//	tp.run(2);
//	system("pause");
//	return 0;
//}


//#include <iostream>
//#include <thread>
//#include <vector>
//#include <string>
//#include <functional>
//#include <future>
//#include <chrono>
//
//using namespace std;
//
//struct task
//{
//	string status;
//	function<void()> func;
//	task(string status, function<void()> func)
//	{
//		this->status = status;
//		this->func = func;
//	}
//};
//
//class threadpool
//{
//public:
//	threadpool()
//	{
//		flag = true;
//		thcount = 0;
//	}
//	~threadpool()
//	{
//
//	}
//	void addTask(function<void()> func)
//	{
//		lock_guard<mutex> mtx(blocker);
//		queue.push_back(task(statuses[0], func));
//	}
//	void run(int threadnum = thread::hardware_concurrency() - 1)
//	{
//		thcount += threadnum;
//		if (thcount > thread::hardware_concurrency() - 1)
//		{
//			cout << "Error:: maximum number of threads reached" << endl;
//			return;
//		}
//		else if (threadnum < 1)
//		{
//			cout << "Error:: the number of threads cannot be negative" << endl;
//			return;
//		}
//		for (int i = 0; i < threadnum; i++)
//		{
//			threads.push_back(thread([this]()
//				{
//					try
//					{
//						while (flag)
//						{
//							unique_lock<mutex>mtx2(blocker);
//							for (int i = 0; i < queue.size(); i++)
//							{
//								if (queue[i].status == statuses[0])
//								{
//									queue[i].status = statuses[1];
//									mtx2.unlock();
//									queue[i].func();
//									mtx2.lock();
//									queue[i].status = statuses[2];
//									break;
//								}
//							}
//						}
//					}
//					catch (const std::exception&)
//					{
//						cout << "Error: exeption was called" << endl;
//						return;
//					}
//				}));
//		}
//		for (auto& x : threads)
//		{
//			x.join();
//		}
//	}
//
//	void end()
//	{
//		flag = false;
//	}
//	string getStatus(int index)
//	{
//		if (index <= 0)
//		{
//			return "Error:: 404";
//		}
//		else if (index > queue.size())
//		{
//			return "Error:: 404";
//		}
//		else
//		{
//			return queue[index - 1].status;
//		}
//	}
//
//private:
//	vector<task> queue;
//	const vector<string> statuses = { "Waiting","In process","Complete" };
//	mutex blocker;
//	vector<thread> threads;
//	bool flag;
//	int thcount;
//};
//
//
//
//
//
//
//void test(int x)
//{
//	this_thread::sleep_for(chrono::milliseconds(8000));
//	cout << "This is cool tekst: " << x << endl;
//}
//
//void test1(int x, int y)
//{
//	this_thread::sleep_for(chrono::milliseconds(1500));
//	cout << "Hello world: " << x + y << endl;
//}
//
//string test2()
//{
//	//this_thread::sleep_for(chrono::milliseconds(500));
//	cout << ":-^)\n";
//	return ":-^)\n";
//}
//
//int main()
//{
//	threadpool tp;
//	thread th([&]() {
//		for (int i = 0; i < 500; i++)
//		{
//			tp.addTask([&]() {test2(); });
//		}
//		tp.addTask([&]() {tp.end(); });
//		});
//	cout << tp.getStatus(4) << endl;
//	tp.run(3);
//	th.join();
//	system("pause");
//}

//using namespace std;
//
//
//int main() 
//{
//	
//
//
//	system("pause");
//	return 0;
//}

//#include <iostream>
//#include <functional>
//#include<vector>
//#include<mutex>
//#include<string>
//#include<chrono>
//#include<atomic>
//
//using namespace std;
//
//struct Task//+
//{
//	function<void()>task;
//	string status;
//	decltype(thread().get_id()) ID;
//	Task(const function<void()>& task, const string& status)
//	{
//		this->task = task;
//		this->status = status;
//	}
//};
//
//class Thread_Pool
//{
//public:
//	const vector<string>status = { "ADDED","FINISHING","THREADED","DONE","CANCELED" };
//
//	Thread_Pool()//+
//	{
//		this->max_thread_number = 0;
//		this->stopped = false;
//	}
//
//	~Thread_Pool()
//	{
//		cancel();
//	}
//
//	const Task& add(const function<void()>& task)//+
//	{
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		this->tasks.emplace_back(Task(task, this->status[0]));
//		const Task& ref = this->tasks[this->tasks.size() - 1];
//		return ref;
//	}
//
//	void start(const unsigned int& number = thread::hardware_concurrency())//+
//	{
//		if (number < 1)
//		{
//			cout << "Number of threads can`t be less than 1!\n";
//			return;
//		}
//		set_thread_number(number);
//		for (int i = 0; i < this->max_thread_number; i++)
//		{
//			vector<Task>& v_ref = this->tasks;
//			mutex& mtx = this->_vec_mtx;
//			pool.push_back(thread([this, &v_ref, &mtx]()
//				{
//					while (!stopped)
//					{
//						for (int j = 0; j < v_ref.size(); j++)
//						{
//							unique_lock<mutex>LOCK(this->_vec_mtx);
//							if (v_ref[j].status == this->status[0])
//							{
//								v_ref[j].status = this->status[2];
//								LOCK.unlock();
//								v_ref[j].task();
//								LOCK.lock();
//								tasks[j].status = this->status[3];
//							}
//						}
//					}
//				}));
//		}
//		for (auto& ref : this->pool)
//			ref.join();
//		while (true)
//		{
//			string ch;
//			cout << "Do you want to finish your tasks?(Y/N)\n";
//			cin >> ch;
//			if (ch == "Y")
//			{
//				unique_lock<mutex>LOCK(this->_vec_mtx);
//				for (int i = 0; i < tasks.size(); i++)
//					if (tasks[i].status == status[0]) tasks[i].status = status[1];
//				LOCK.unlock();
//				finish();
//				break;
//			}
//			else if (!cin.good())
//			{
//				cin.clear();
//				cin.ignore(10000, '\n');
//				cout << "Invalid symbols found!\n";
//			}
//			else
//			{
//				cancel();
//				break;
//			}
//		}
//	}
//
//	void cancel()//+
//	{
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		for (int i = 0; i < this->tasks.size(); i++)
//			if (this->tasks[i].status != this->status[3])this->tasks[i].status = this->status[4];
//	}
//
//	void stop()//+
//	{
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		this->stopped = true;
//	}
//
//	vector<string> get_statuses()
//	{
//		vector<string>G;
//		lock_guard<mutex>LOCK(this->_vec_mtx);
//		for (int i = 0; i < this->tasks.size(); i++)
//			G.push_back(this->tasks[i].status);
//		return G;
//	}
//private:
//
//	atomic<bool>stopped;
//
//	mutex _vec_mtx;
//
//	vector<Task>tasks;
//
//	vector<thread> pool;
//
//	unsigned int max_thread_number;
//
//	void set_thread_number(const unsigned int& number = thread::hardware_concurrency());//+
//
//	void finish()
//	{
//		for (int i = 0; i < this->max_thread_number; i++)
//		{
//			vector<Task>& v_ref = this->tasks;
//			mutex& mtx = this->_vec_mtx;
//			pool[i] = thread([this, &v_ref, &mtx]()
//				{
//					for (int j = 0; j < v_ref.size(); j++)
//					{
//						unique_lock<mutex>LOCK(this->_vec_mtx);
//						if (v_ref[j].status == this->status[1])
//						{
//							v_ref[j].status = this->status[2];
//							LOCK.unlock();
//							v_ref[j].task();
//							LOCK.lock();
//							tasks[j].status = this->status[3];
//						}
//					}
//				});
//		}
//		for (auto& ref : this->pool)
//			ref.join();
//		cout << "Finished\n";
//		cancel();
//	}
//};
//
//void Thread_Pool::set_thread_number(const unsigned int& number)//+
//{
//	int max = thread::hardware_concurrency();
//	if (number >= max)
//	{
//		while (true)
//		{
//			cout << "WARNING! ALL " << max << " CPU`S WILL BE USED! DO YOU WANT TO CONTINUE?(Y/N)\n";
//			if (cin.get() == 'Y')
//			{
//				this->max_thread_number = max;
//				break;
//			}
//			else if (!cin.good())
//			{
//				cin.clear();
//				cin.ignore(10000, '\n');
//				cout << "Invalid symbols found!\n";
//			}
//			else
//			{
//				this->max_thread_number = number;
//				break;
//			}
//		}
//	}
//	else
//	{
//		this->max_thread_number = number;
//	}
//	cout << "SET COMPLETED\n";
//}
//
//int f1()
//{
//	//this_thread::sleep_for(chrono::seconds(6));
//	for (int i = 0; i < 1000; i++)
//		cout << 2;
//	cout << "F1\n";
//	return 10;
//}
//
//int f2(int a)
//{
//	//this_thread::sleep_for(chrono::seconds(3));
//	for (int i = 0; i < 1000; i++)
//		cout << 1;
//	cout << " F2\n";
//	return a;
//}
//
//
//int main()
//{
//	int a;
//	Thread_Pool tp;
//	function<void()>ff1 = []() {f1(); };
//	function<void()>ff2 = [&]() {a = f2(10); };
//	for (int i = 0; i < 10; i++)
//	{
//		tp.add(ff1);
//		tp.add(ff2);
//		tp.add(ff1);
//		tp.add(ff2);
//		tp.add(ff1);
//		tp.add(ff2);
//	}
//	tp.add(function<void()>([&tp]() {tp.stop(); }));
//	//thread t(&Thread_Pool::start, &tp,4);
//	tp.start();
//	tp.add(function<void()>([]() {f1(); }));
//	tp.add(function<void()>([]() {f2(5); }));
//	//tp.stop();
//	vector<string>v = tp.get_statuses();
//	//t.join();
//
//	cout << a << endl;
//	for (auto au : v)
//		cout << au << endl;
//
//	system("pause");
//	return 0;
//}



//#include <thread>
//#include <mutex>
//#include <functional>
//#include <vector>
//#include <queue>
//#include <condition_variable>
//#include <iostream>
//#include <chrono>
//#include <time.h>
//using namespace std;
//
//#define MAX_THREADS std::thread::hardware_concurrency() - 1;
//
//class Th_pool {
//public:
//	void resize(int newCount) {
//		int tmp = MAX_THREADS;
//		if (newCount <= 0 || newCount > tmp) {
//
//
//		}
//		else {
//			if (newCount > numThreads) {
//				uint8_t tmp = numThreads;
//				numThreads = newCount;
//				Pool.resize(numThreads);
//				Th_id.resize(numThreads);
//				for (int i = tmp; i != numThreads; ++i) {
//
//					Pool.emplace_back(move(thread(&Th_pool::thread_while, this)));
//					Th_id.emplace_back(Pool.back().get_id());
//					Pool.back().detach();
//				}
//			}
//			else {
//
//				numThreads = newCount;
//				Pool.resize(newCount);
//				Th_id.resize(newCount);
//			}
//		}
//	}
//
//private:
//
//	class task {
//	private:
//		function<void(int)> func;
//		int info;
//		string stat;
//		bool trig = 1;
//	public:
//		~task() {}
//		task(function<void(int)> ff, int inf) {
//			func = ff;
//			info = inf;
//			stat = "in the queue";
//
//		}
//		void performed_f() {
//			trig = 0;
//			stat = "performed";
//			trig = 1;
//		}
//		void completed_f() {
//			trig = 0;
//			stat = "completed";
//			trig = 1;
//		}
//		void execute() {
//
//			func(info);
//
//		}
//		string statys() {
//			while (!trig) {
//
//			}
//			return stat;
//		}
//	};
//	int numThreads;
//	vector<thread> Pool;
//	vector<thread::id> Th_id;
//	vector<shared_ptr<task>> taskQueue;
//	condition_variable thread_c;
//	mutex taskMutex;
//
//	void thread_while() {
//		srand(0);
//		while (true) {
//
//			for (int i = 0; i < taskQueue.size(); i++) {
//				shared_ptr<task> cc = taskQueue[i];
//				string rr = this->statys(cc);
//
//				if (rr == "in the queue") {
//
//					taskMutex.lock();
//					(*cc).performed_f();
//					taskMutex.unlock();
//					(*cc).execute();
//
//					(*cc).completed_f();
//
//				}
//
//			}
//
//			unique_lock<mutex> lock(taskMutex);
//			thread_c.wait(lock, [this] {return !taskQueue.empty(); });
//
//			bool tr = 1;
//
//			for (int i = 0; i < Th_id.size(); i++) {
//
//				if (Th_id[i] == this_thread::get_id()) {
//					tr = 0;
//					break;
//				}
//
//			}
//			if (tr) {
//				break;
//			}
//		}
//	}
//public:
//	Th_pool(int th_size) : numThreads(th_size) {
//		int tmp = MAX_THREADS;
//		if (numThreads > tmp) {
//			numThreads = tmp;
//		}
//		Pool.reserve(numThreads);
//		Th_id.reserve(numThreads);
//		for (int i = 0; i != numThreads; ++i) {
//
//			Pool.emplace_back(thread(&Th_pool::thread_while, this));
//			Th_id.emplace_back(Pool.back().get_id());
//			Pool.back().detach();
//		}
//
//
//
//	}
//	shared_ptr<task> push_task(function<void(int)> func, int info) {
//		unique_lock<mutex> lock(taskMutex);
//		task tt(func, info);
//
//		taskQueue.push_back(std::make_shared<task>(std::move(tt)));
//		thread_c.notify_one();
//		return taskQueue.back();
//	}
//	string statys(shared_ptr<task> tas) {
//
//		string rr = (*tas).statys();
//
//		return rr;
//	}
//
//	~Th_pool() {
//		this_thread::sleep_for(chrono::milliseconds(1000));
//		while (this->statys(taskQueue[taskQueue.size() - 1]) != "completed") {
//
//		}
//		Th_id.resize(0);
//		this_thread::sleep_for(chrono::milliseconds(1000));
//
//	}
//};