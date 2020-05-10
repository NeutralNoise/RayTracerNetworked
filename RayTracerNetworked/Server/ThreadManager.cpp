#include "ThreadManager.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Config.h"
#include "ThreadFunctions.h"

ThreadManager::ThreadManager()
{
	m_currentThreadCount = 1;
	m_isRunning = true;
	int cpuCount = SDL_GetCPUCount();
	if (Config::MaxThreadCount < cpuCount) {
		m_maxThreadCount = Config::MaxThreadCount;
	}
	else {
		m_maxThreadCount = cpuCount;
	}
	p_taskManager = nullptr;
}

ThreadManager::ThreadManager(TaskManager * tm)
{
	m_currentThreadCount = 1;
	m_isRunning = true;
	int cpuCount = SDL_GetCPUCount();
	if (Config::MaxThreadCount < cpuCount) {
		m_maxThreadCount = Config::MaxThreadCount;
	}
	else {
		m_maxThreadCount = cpuCount;
	}
	p_taskManager = tm;
}

void ThreadManager::CreateThread()
{
	//Check if we can create a new thread.
	if (m_currentThreadCount == m_maxThreadCount) {
		return;
	}
	m_threads.push_back(std::thread(TaskPerThread, p_taskManager, &m_isRunning));
	m_currentThreadCount += 1;
}

void ThreadManager::JoinAllThreads()
{
	m_runningMutex.lock();
	m_isRunning = false;
	m_runningMutex.unlock();
	for (size_t i = 0; i < m_threads.size(); i++) {
		if (m_threads[i].joinable()) {
			m_threads[i].join();
			m_currentThreadCount--;
		}
	}
}

std::mutex ThreadManager::m_runningMutex;