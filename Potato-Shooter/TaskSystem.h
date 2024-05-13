#include <vector>
#include <algorithm>
#include <iterator>  
#include "Task.h"
#include "DelayTask.h"

class TaskSystem
{
public:
	TaskSystem(ServiceLocator& locator);
	~TaskSystem();

	template<typename T>
	void add()
	{
		T* task = new T();
		Task* base = task;

		base->initialize(locator);
		tasks.emplace_back(base);
	}

	void delay(int miliseconds)
	{
		Task* base = new DelayTask(miliseconds);

		base->initialize(locator);
		tasks.emplace_back(base);
	}

	void clear()
	{
		current_index = 0;

		for (Task* task : tasks)
		{
			delete task;
		}

		tasks.clear();
		tasks.shrink_to_fit();
	}

	void update(const double& dt);
	void draw();
	void post_draw();
	bool finished();

private:
	ServiceLocator& locator;

	std::vector<Task*> tasks;

	int current_index = 0;
	int executing_count = 0;

	void start_task();
};

