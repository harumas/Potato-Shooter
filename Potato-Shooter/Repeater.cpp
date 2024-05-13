#include "Repeater.h"

Repeater::Repeater(double interval, std::function<void(void)> action)
	:interval((long long)(interval * 1000000)),
	next_time((long long)(interval * 1000000)),
	action(action),
	start_time(0),
	elapsed_time(0) {
};

void Repeater::update() {
	if (elapsed_time == 0)
	{
		start_time = GetNowHiPerformanceCount();
	}

	elapsed_time = GetNowHiPerformanceCount() - start_time;

	if (elapsed_time >= next_time)
	{
		action();
		next_time += interval;
	}
}
