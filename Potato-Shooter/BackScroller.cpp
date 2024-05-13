#include "Module.h"
#include "BackScroller.h"

BackScroller::BackScroller(ResourceHandler* handler)
{
	bg_handle = handler->load_graph("bg.png");

	//画像の高さを算出
	int bg_w, bg_h;
	GetGraphSize(bg_handle, &bg_w, &bg_h);
	int aspect = bg_h / bg_w;
	height = App::screen_w * aspect;

	bg2_y = -height;
}

void BackScroller::update(const double& dt)
{
	bg1_y += move_per_sec * dt;
	bg2_y += move_per_sec * dt;
}

void BackScroller::draw()
{
	int bg1_y2 = (int)bg1_y + height; //背景1枚めの高さ
	int bg2_y2 = (int)bg2_y + height; //背景2枚めの高さ

	DrawExtendGraph(0, (int)bg1_y, App::screen_w, bg1_y2, bg_handle, TRUE);
	DrawExtendGraph(0, (int)bg2_y, App::screen_w, bg2_y2, bg_handle, TRUE);


	//背景が全て画面外に出たら一番下に持ってくる
	if ((int)bg1_y > App::screen_h)
	{
		bg1_y = bg2_y - height;
	}

	if ((int)bg2_y > App::screen_h)
	{
		bg2_y = bg1_y - height;
	}
}
