#include "TaskQueue.h"
#include <mutex>

std::mutex g_lock;

TaskQueue::TaskQueue()
{
}


int TaskQueue::addTask(TTask task)
{
	g_lock.lock();
	tasksQueue->push(task);
	g_lock.unlock();

	return 1;
}

TTask TaskQueue::popTask()
{
	TTask result;

	g_lock.lock();
	if (tasksQueue->empty()) {
		result = NULL;
	}
	else {
		result = tasksQueue->front();
		tasksQueue->pop();
	}
	g_lock.unlock();

	return result;
}
