#pragma once

#include "EnemyB.h"
#include <numbers> 

using namespace std;

EnemyB::EnemyB(ServiceLocator& locator) :
	collider(1, &position, 25.0f, [this](int damage) { this->damage(damage); }), //当たり判定
	shoot_repeater(1, [this]() { weapons->shoot(Vector2(0, 250)); }), //自動発射
	target(locator.resolve<Player>()->get_position()), //回転先を設定
	Entity(locator)
{
	game_score = locator.resolve<GameScore>();

	//コライダーを登録 
	simulator_ptr = locator.resolve<CollisionSimulator>();
	simulator_ptr->add_reciever(&collider);

	//画像のロード 
	img_handle = handler_owner->load_graph("enemy_shooter.png");
	bgm_handle = handler_owner->load_audio("score.mp3");

	//武器の初期化 
	weapons = new WeaponCollection(&position, handler_owner.get(), simulator_ptr.get());
	weapons->set_channels(0);

	//発射先を設定 
	WeaponB* weapon = weapons->add_weapon<WeaponB>();
	weapon->set_target(target);
};

void EnemyB::damage(int damage)
{
	hit_point.decrease(damage);
}

void EnemyB::spawn(Vector2 pos, Vector2 initial_velocity)
{
	position = pos;
	velocity_mov = initial_velocity;
	rotation = 0;
	pos_delta.x = pos.x;
	pos_delta.y = pos.y;

	next_rotation = get_next_rotation();
	is_targeting = true;

	enable();
}

void EnemyB::update_status()
{
	const	int radius = (int)(collider.collision.radius);
	const Vector2Int& pos = (Vector2Int)position;

	bool out_of_h = pos.y > App::screen_h + radius;
	bool is_dead = hit_point.current() <= 0;

	//画面上部の外に出たら or 死んでたら
	if (out_of_h || is_dead)
	{
		if (death_delay == nullptr)
		{
			death_delay = new DelayPromise(300);

			if (is_dead)
			{
				game_score->add(15);
				explode_effect.play(position, 0.3);
				PlaySoundMem(bgm_handle, DX_PLAYTYPE_BACK);
			}

			hide();
		}
		else if (death_delay->complete())
		{
			disable();
		}
	}
}

void EnemyB::update(const double& dt)
{
	if (!enabled) return;

	if (is_showing)
	{
		update_movement(dt);
		shoot_repeater.update();
		weapons->update(dt);
	}

	update_status();
};


void EnemyB::update_movement(const double& dt)
{
	position += velocity_mov * (float)dt;
	rotation = get_next_rotation();
}

double EnemyB::get_next_rotation()
{
	const Vector2& to = (*target - position).normalized();

	if (to.x == 0)
	{
		return (to.y >= 0 ? 1 : -1) * PI / 2.0f;
	}
	else if (to.x < 0)
	{
		return PI + PI / 2.0f + atan(to.y / to.x);
	}
	else
	{
		return PI / 2.0f + atan(to.y / to.x);
	}
}

void EnemyB::draw()
{
	if (!enabled || !is_showing) return;

	const Vector2Int& pos = (Vector2Int)position;
	DrawRotaGraph(pos.x, pos.y, 4, rotation, img_handle, TRUE);

	weapons->draw();
};

void EnemyB::enable()
{
	enabled = true;
	collider.simulated = true;
	is_showing = true;
};

void EnemyB::hide()
{
	collider.simulated = false;
	weapons->reset_all();
	is_showing = false;
}

void EnemyB::disable()
{
	enabled = false;
};

