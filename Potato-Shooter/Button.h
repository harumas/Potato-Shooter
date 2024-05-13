#pragma once
#include "GUI.h" 

class Button :public GUI
{
public:
	Button(int x, int y, int width, int height);

protected:
	const int x;
	const int y;
	const int half_width;
	const int half_height;

private:
	bool in_range(int mouse_x, int mouse_y) override;
};

