#pragma once

class HP
{
public:
	HP(int initial, int max);
	int current();
	void increase(int delta);
	void decrease(int delta);
	void copy(const HP& other);

private:
	int max = 0;
	int current_point = 0;
};

