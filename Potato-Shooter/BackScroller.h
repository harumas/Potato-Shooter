#pragma once

class BackScroller
{
	int bg_handle = 0;
	int height = 0;
	int move_per_sec = 20;
	double bg1_y = 0;
	double bg2_y = 0;

public:
	BackScroller(ResourceHandler* handler);
	void update(const double& dt);
	void draw();
	void reset();
};
