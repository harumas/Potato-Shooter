#pragma once
#include "Effect.h" 

Effect::Effect(string data_path, int count, int width, double ext_rate) :
	ext_rate(ext_rate),
	frame_count(count),
	GUI()
{
	//エフェクトシートのロード（現状は横一列&正方形のみ対応） 
	frames = new int[count];
	LoadDivGraph((".\\media\\" + data_path).c_str(), count, count, 1, width, width, frames);
	GUIUpdater::register_gui(this);
}

Effect::~Effect()
{
	delete frames;
}

void Effect::load(ServiceLocator* locator)
{
	timer = locator->resolve<Time>();
}

void Effect::play(Vector2 point, double duration)
{
	draw_point = (Vector2Int)point;
	frame_time_unit = duration / frame_count; //1フレームに要する時間
	enable();
}

void Effect::update(int mouse_x, int mouse_y, bool is_mouse_down, bool is_mouse_up)
{
	//最大フレーム数に達したら 
	if (current_frame >= frame_count)
	{
		current_frame = 0;
		current_time = 0;
		disable();
	}
	else
	{
		//次に更新する時間
		double next_time = frame_time_unit * (current_frame + 1);

		if (current_time >= next_time)
		{
			current_frame++;
		}
	}

	current_time += timer->get_delta();
}


void Effect::draw()
{
	DrawRotaGraph(draw_point.x, draw_point.y, ext_rate, 0, frames[current_frame], TRUE);
}

bool Effect::in_range(int mouse_x, int mouse_y)
{
	return false;
}

