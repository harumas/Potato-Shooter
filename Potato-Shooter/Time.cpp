#include "Time.h"

void Time::init()
{
	delta = 0.000001;
	prev_time = GetNowHiPerformanceCount();
}

double Time::get_delta()
{
	return delta * time_scale;
}

double Time::get_time_scale()
{
	return time_scale;
}

void Time::set_time_scale(double scale)
{
	time_scale = scale;
}

void Time::update()
{
	now_time = GetNowHiPerformanceCount();
	delta = (now_time - prev_time) / 1000000.0; //フレーム間の時間を算出
	prev_time = now_time;
}
