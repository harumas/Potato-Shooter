#include "HP.h"
#include "Extension.h"

HP::HP(int initial, int max)
{
	//maxが0より小さかったら全て無効とする
	if (max < 0)
	{
		max = 0;
		initial = 0;
	}

	if (initial > max)
	{
		initial = max;
	}

	this->max = max;
	current_point = initial;
}

int HP::current()
{
	return current_point;
}

void HP::increase(int delta)
{
	current_point += delta;
	current_point = clamp_int(0, max, current_point);
}

void HP::decrease(int delta)
{
	current_point -= delta;
	current_point = clamp_int(0, max, current_point);
}

void HP::copy(const HP& other)
{
	max = other.max;
	current_point = other.current_point;
}
