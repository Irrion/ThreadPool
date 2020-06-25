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
	threadpool th(5);
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


