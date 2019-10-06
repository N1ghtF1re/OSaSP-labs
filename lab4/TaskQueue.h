#pragma once
#include <queue>
#include <functional>

//typedef void (* TTask)(void);
typedef std::function<void()> TTask;


class TaskQueue
{
public:
	TaskQueue();
	int addTask(TTask task);
	TTask popTask();
private:
	std::queue<TTask>* tasksQueue = new std::queue<TTask>;
};

