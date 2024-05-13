#include "MinimumButton.h"

MinimumButton::MinimumButton(int x, int y, int width, int height, string text) :
	text(text),
	Button(x, y, width, height)
{
	GUIUpdater::register_gui(this);
}

void MinimumButton::load(ServiceLocator* locator)
{
	cursor = locator->resolve<Cursor>();

	default_img_handle = handler->load_graph("button.png");
	on_click_handle = handler->load_graph("button_pressed.png");
	font_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5, DX_FONTTYPE_EDGE);
	se_handle = handler->load_audio("button.mp3");

	calc_draw_info();
}


void MinimumButton::update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up)
{
	GUI::update(mouse_x, mouse_y, is_mouse_down, is_mouse_up);

	if (mouse_up)
	{
		on_click_delay = new DelayPromise(500);
		mouse_up = false;
		delay_started = true;
	}

	if (delay_started && on_click_delay->complete())
	{
		on_click();
		delay_started = false;
	}
}


void MinimumButton::calc_draw_info()
{
	const char* str = text.c_str();
	half_font_height = GetFontSizeToHandle(font_handle);
	half_font_width = GetDrawStringWidthToHandle(str, (int)strlen(str), font_handle);
}

void MinimumButton::draw()
{
	int handle = is_mouse_down ? on_click_handle : default_img_handle;
	DrawExtendGraph(x - half_width, y - half_height, x + half_width, y + half_height, handle, TRUE);
	DrawRotaStringToHandle(x - half_font_width, y - half_font_height - 5, 2, 2, 0, 0, 0, GetColor(255, 255, 255), font_handle, GetColor(104, 97, 67), 0, text.c_str());
}

void MinimumButton::on_enter()
{
	cursor->set_cursor(IDC_HAND);
}

void MinimumButton::on_exit()
{
	cursor->set_cursor(IDC_ARROW);
	is_mouse_down = false;
}

void MinimumButton::on_mouse_down()
{
	is_mouse_down = true;
	PlaySoundMem(se_handle, DX_PLAYTYPE_BACK);
}

void MinimumButton::on_mouse_up()
{
	if (is_mouse_down)
	{
		is_mouse_down = false;
		mouse_up = true;
	}
}

void MinimumButton::on_disable()
{
	cursor->set_cursor(IDC_ARROW);
}
