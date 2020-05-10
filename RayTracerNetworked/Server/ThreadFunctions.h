#ifndef THREAD_FUNCTIONS_H_INCLUDED
#define THREAD_FUNCTIONS_H_INCLUDED

class TaskManager;

extern void TaskPerThread(TaskManager * tm, bool *isRunning);

#endif // !THREAD_FUNCTIONS_H_INCLUDED

