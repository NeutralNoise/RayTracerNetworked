#ifndef TASK_MANAGER_H_INCLUDED
#define TASK_MANAGER_H_INCLUDED
#include <queue>
#include <mutex>
#include "Task.h"

class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	void AddTask(const int &chunk, const int &width, const int &height);
	void AddTask(const Task &t);
	bool HasTask();
	Task GetTask();

	void AddCompletedTask(const int &x, const int &y, const ColourRGBA &colour);
	void AddCompletedTask(const CompletedTask &t);
	bool HasCompletedTask();
	CompletedTask GetCompletedTask();

private:
	std::queue<Task> m_tasks;
	std::queue<CompletedTask> m_completed;
	std::mutex m_taskMutex;
	std::mutex m_ctaskMutex;
};

#endif // !TASK_MANAGER_H_INCLUDED

