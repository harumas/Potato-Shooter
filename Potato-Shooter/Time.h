#pragma once
#include "DxLib.h"

class Time {
public:
	void init();
	double get_delta();
	double get_time_scale();
	void set_time_scale(double scale);
	void update();

private:
	double delta;
	double time_scale = 1;
	LONGLONG start_time;
	LONGLONG now_time;
	LONGLONG prev_time;
};
