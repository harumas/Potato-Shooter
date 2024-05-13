#include "Player.h"

PlayerStatus::PlayerStatus(ResourceHandler* handler)
{
	heart_handle = handler->load_graph("heart.png");
	heart_half_handle = handler->load_graph("heart_half.png");
}

void PlayerStatus::increase(int delta)
{
	hit_point.increase(delta);

	if (hit_point.current() <= 0)
	{
		on_death();
	}
}

void PlayerStatus::decrease(int delta)
{
	hit_point.decrease(delta);

	if (hit_point.current() <= 0)
	{
		on_death();
	}
}

void PlayerStatus::draw()
{
	//ハートの描画(2hp = 1ハート)
	for (int i = 0; i < hit_point.current() / 2; i++)
	{
		DrawRotaGraph(i * 22 + 20, App::screen_h - 20, 1.5, 0, heart_handle, TRUE);
	}

	//半ハートの描画
	if (hit_point.current() % 2 != 0)
	{
		DrawRotaGraph((hit_point.current() / 2) * 22 + 20, App::screen_h - 20, 1.5, 0, heart_half_handle, TRUE);
	}
}

void PlayerStatus::reset()
{
	hit_point = HP(20, 20);
}
