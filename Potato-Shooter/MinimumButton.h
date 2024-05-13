#pragma once

#include <string>
#include "Button.h"
#include "DelayPromise.h"
#include "ResourceHandler.h" 

class MinimumButton :public Button
{
public:
	MinimumButton(int x, int y, int width, int height, std::string text);
	void load(ServiceLocator* locator) override;
	void draw() override;
	void update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up) override;
	void calc_draw_info();

	std::function<void(void)> on_click;

private:
	const std::string text;

	shared_ptr<Cursor> cursor;

	int default_img_handle = 0;
	int on_click_handle = 0;
	int font_handle = 0;
	int se_handle = 0;

	bool is_mouse_down = false;
	bool mouse_up = false;
	bool delay_started = false;

	//描画座標キャッシュ 
	int half_font_width;
	int half_font_height;

	DelayPromise* on_click_delay = nullptr;

	void on_enter() override;
	void on_exit() override;
	void on_mouse_down() override;
	void on_mouse_up() override;
	void on_disable() override;
};

