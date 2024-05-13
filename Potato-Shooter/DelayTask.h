#include "Task.h"
#include "DxLib.h"


class DelayTask :public Task
{
public:
	DelayTask(int miliseconds) :delay_time(miliseconds) {};

	void initialize(ServiceLocator& locator) override {};

	bool is_starting() override
	{
		return current < start_time + delay_time;
	}

	void start() override
	{
		if (is_first)
		{
			start_time = GetNowCount();
			is_first = false;
		}

		current = GetNowCount();
	}

	bool is_executing() override
	{
		return false;
	}

	void execute(const double& dt) override {};
	void draw() override {};

private:
	const int delay_time;
	int start_time = 0;
	int current = 0;
	bool is_first = true;
};

