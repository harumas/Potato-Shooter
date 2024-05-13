#pragma once

#include "Task.h"
#include "Player.h"
#include <memory>

class TutorialTask :public Task
{
public:
	void initialize(ServiceLocator& locator) override
	{
		device = locator.resolve<Device>();
		font_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5);
		panel_width = App::screen_w - panel_offset * 2;
	}

	bool is_starting() override
	{
		return !start_button_pressed;
	}

	void start() override
	{
		start_button_pressed = device->is_key_down(KEY_INPUT_Z);
	}

	bool is_executing() override
	{
		return !start_button_pressed;
	}

	void execute(const double& dt) override {};

	void draw() override
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(panel_offset, panel_offset, App::screen_w - panel_offset, App::screen_h - panel_offset, GetColor(80, 80, 80), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRotaStringToHandle(panel_offset + 125, panel_offset + 20, 2, 2, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "～操作方法～");
		DrawRotaStringToHandle(panel_offset + 90, panel_offset + 80, 2, 2, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "移動: WASD or ↑←↓→");
		DrawRotaStringToHandle(panel_offset + 90, panel_offset + 120, 2, 2, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "発射: Z");
		DrawRotaStringToHandle(panel_offset + 125, panel_offset + 200, 2, 2, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "Z キーでスタート");


		DrawRotaStringToHandle(App::screen_w - panel_offset - 100, App::screen_h - panel_offset + 10, 1, 1, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "デバッガー向けショートカット");
		DrawRotaStringToHandle(App::screen_w - panel_offset - 100, App::screen_h - panel_offset + 30, 1, 1, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "自動発射モード: O");
		DrawRotaStringToHandle(App::screen_w - panel_offset - 100, App::screen_h - panel_offset + 50, 1, 1, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "自滅: K");
		DrawRotaStringToHandle(App::screen_w - panel_offset - 100, App::screen_h - panel_offset + 70, 1, 1, 0, 0, 0, GetColor(255, 255, 255), font_handle, 0, FALSE, "当たり判定表示: I");
	};

private:
	std::shared_ptr<Device> device;

	bool start_button_pressed = false;
	int panel_offset = 100;
	int panel_width;
	int font_handle;
};


