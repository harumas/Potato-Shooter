#include "Button.h"

Button::Button(int x, int y, int width, int height) :
	x(x), y(y), half_width(width / 2), half_height(height / 2), GUI()
{}

bool Button::in_range(int mouse_x, int mouse_y)
{
	bool in_range_w = mouse_x > (x - half_width) && mouse_x < (x + half_width);
	bool in_range_h = mouse_y > (y - half_height) && mouse_y < (y + half_height);

	return in_range_w && in_range_h;
}
