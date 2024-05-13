#include "Extension.h"

std::mt19937 rand_engine;

void init_rand()
{
	std::random_device seed_device;
	rand_engine.seed(seed_device());
	srand((unsigned int)time(NULL));
}

//整数のランダム値を生成 
int rand_int(int min, int max)
{
	return rand_engine() % (max - min + 1) + min;
}


//valueをmin ~ maxに収める
float clamp(float min, float max, float value)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

//valueをmin ~ maxに収める
int clamp_int(int min, int max, int value)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

//valueを0~maxでループさせる 
float repeat(float value, float max)
{
	return value - std::floorf(value / max) * max;
}

double deg_to_rad(double deg)
{
	return deg * (PI / 180.0);
}
