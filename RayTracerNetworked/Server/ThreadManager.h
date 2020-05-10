#ifndef THREAD_MANAGER_H_INCLUDED
#define THREAD_MANAGER_H_INCLUDED
#include <thread>
#include <vector>
#include <mutex>

class TaskManager;

class ThreadManager
{
public:
	ThreadManager();
	ThreadManager(TaskManager *tm);
	~ThreadManager() {};

	void CreateThread();

	void JoinAllThreads();

	static std::mutex m_runningMutex;
private:
	int m_currentThreadCount;
	int m_maxThreadCount;
	std::vector<std::thread> m_threads;
	TaskManager * p_taskManager;
	bool m_isRunning;
};

#endif // !THREAD_MANAGER_H_INCLUDED

