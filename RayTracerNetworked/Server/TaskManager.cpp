#include "TaskManager.h"

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::AddTask(const int & chunk, const int & width, const int & height)
{
	m_taskMutex.lock();
	m_tasks.push(Task(chunk, width, height));
	m_taskMutex.unlock();
}

void TaskManager::AddTask(const Task &t)
{
	m_taskMutex.lock();
	m_tasks.push(t);
	m_taskMutex.unlock();
}

bool TaskManager::HasTask()
{
	bool has = false;
	//NOTE should this just try lock?
	m_taskMutex.lock();
	if (m_tasks.size()) {
		has = true;
	}
	m_taskMutex.unlock();
	return has;
}

Task TaskManager::GetTask()
{
	Task rtn;
	m_taskMutex.lock();
	if (m_tasks.size()) {
		rtn = m_tasks.front();
		m_tasks.pop();
	}
	m_taskMutex.unlock();
	return rtn;
}

void TaskManager::AddCompletedTask(const int & x, const int & y, const ColourRGBA & colour)
{
	m_ctaskMutex.lock();
	m_completed.push(CompletedTask(x, y, colour));
	m_ctaskMutex.unlock();
}

void TaskManager::AddCompletedTask(const CompletedTask & t)
{
	m_ctaskMutex.lock();
	m_completed.push(t);
	m_ctaskMutex.unlock();
}

bool TaskManager::HasCompletedTask()
{
	bool has = false;
	//NOTE should this just try lock?
	m_ctaskMutex.lock();
	if (m_completed.size()) {
		has = true;
	}
	m_ctaskMutex.unlock();
	return has;
}

CompletedTask TaskManager::GetCompletedTask()
{
	CompletedTask rtn;
	m_ctaskMutex.lock();
	if (m_completed.size()) {
		rtn = m_completed.front();
		m_completed.pop();
	}
	m_ctaskMutex.unlock();

	return rtn;
}
