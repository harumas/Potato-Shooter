#include "GUI.h"
#include "GUI.h"

GUI::GUI()
{
}

void GUI::set_handler(ResourceHandler* handler)
{
	this->handler = handler;
}

bool GUI::is_enabled()
{
	return enabled;
}

void GUI::enable()
{
	on_enable();
	enabled = true;
}

void GUI::disable()
{
	on_disable();
	enabled = false;
}

void GUI::update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up)
{
	bool is_stay = in_range(mouse_x, mouse_y);

	//マウスがGUIに入ったとき 
	if (!prev_enter && is_stay)
	{
		prev_enter = true;
		on_enter();
	}

	//マウスがGUIから出たとき
	if (prev_enter && !is_stay)
	{
		prev_enter = false;
		on_exit();
	}

	//マウスがGUIをクリックしたとき
	if (is_mouse_down && is_stay)
	{
		on_mouse_down();
	}

	//マウスがGUIを離したとき
	if (is_mouse_up && is_stay)
	{
		on_mouse_up();
	}
}
