#pragma once

#include "TaskQueue.h"
class TasksExecutor
{
private:
	TaskQueue _queue;
	int _maxThreadsCount;
public:
	TasksExecutor(TaskQueue queue);

	void startExecution(int maxThreadsCount);
};

