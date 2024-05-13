#include "TaskSystem.h"

TaskSystem::TaskSystem(ServiceLocator& locator) :locator(locator) {}

void TaskSystem::update(const double& dt)
{
	start_task();

	for (int i = 0; i < current_index + 1; i++)
	{
		Task* current = tasks[i];

		if (current->is_executing())
		{
			current->execute(dt);
		}
	}
}

void TaskSystem::start_task()
{
	Task* task = tasks[current_index];

	//タスクが開始中は次のタスクにいかない
	if (task->is_starting())
	{
		task->start();
	}
	else
	{
		if (current_index >= tasks.size() - 1)
			return;

		current_index++;
	}
}

void TaskSystem::draw()
{
	for (int i = 0; i < current_index + 1; i++)
	{
		Task* current = tasks[i];

		if (current->is_executing())
		{
			current->draw();
		}
	}
}

void TaskSystem::post_draw()
{
	executing_count = 0;

	for (int i = 0; i < current_index + 1; i++)
	{
		Task* current = tasks[i];

		if (current->is_executing())
		{
			current->post_draw();
			executing_count++;
		}
	}
}


bool TaskSystem::finished()
{
	//全てのタスクが停止したか
	return current_index >= tasks.size() - 1 && !tasks[current_index]->is_starting() && executing_count == 0;
}

TaskSystem::~TaskSystem()
{
	for (Task* task : tasks)
	{
		delete task;
	}

	tasks.clear();
	tasks.shrink_to_fit();
}





