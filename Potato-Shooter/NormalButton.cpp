#include "NormalButton.h"

NormalButton::NormalButton(int x, int y, int width, int height, string text) :
	text(text),
	Button(x, y, width, height)
{
	GUIUpdater::register_gui(this);
}

void NormalButton::load(ServiceLocator* locator)
{
	cursor = locator->resolve<Cursor>();

	default_img_handle = handler->load_graph("button.png");
	on_click_handle = handler->load_graph("button_pressed.png");
	se_handle = handler->load_audio("button.mp3");
	font_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5, DX_FONTTYPE_EDGE);
}


void NormalButton::update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up)
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

void NormalButton::draw()
{
	int handle = is_mouse_down ? on_click_handle : default_img_handle;
	DrawExtendGraph(x - half_width, y - half_height, x + half_width, y + half_height, handle, TRUE);

	DrawRotaStringToHandle(x - 43, y - 30, 4, 4, 0, 0, 0, GetColor(255, 255, 255), font_handle, GetColor(104, 97, 67), 0, text.c_str());
}

void NormalButton::on_enter()
{
	cursor->set_cursor(IDC_HAND);
}

void NormalButton::on_exit()
{
	cursor->set_cursor(IDC_ARROW);
	is_mouse_down = false;
}

void NormalButton::on_mouse_down()
{
	is_mouse_down = true;
	PlaySoundMem(se_handle, DX_PLAYTYPE_BACK);
}

void NormalButton::on_mouse_up()
{
	if (is_mouse_down)
	{
		is_mouse_down = false;
		mouse_up = true;
	}
}

void NormalButton::on_disable()
{
	cursor->set_cursor(IDC_ARROW);
}
