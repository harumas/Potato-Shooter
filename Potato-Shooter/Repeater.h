#pragma once
#include <functional> 
#include  "DxLib.h"

class Repeater
{
private:
	const long long interval;
	const std::function<void(void)> action;

	LONGLONG start_time;
	LONGLONG elapsed_time;
	LONGLONG next_time;

public:
	Repeater(double interval, std::function<void(void)> action);
	void update();
};
