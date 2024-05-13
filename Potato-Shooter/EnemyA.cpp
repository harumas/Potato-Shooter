#include "EnemyA.h" 
#include "WeaponA.h" 

EnemyA::EnemyA(ServiceLocator& locator, bool is_rotate) :
	collider(1, &position, 25.0f, [this](int damage) { this->damage(damage); }), //当たり判定
	shoot_repeater(1, [this]() { weapons->shoot(Vector2(0, 300)); }), //自動発射
	is_rotate(is_rotate), //回転するか
	Entity(locator)
{
	game_score = locator.resolve<GameScore>();

	//コライダーを登録 
	simulator_ptr = locator.resolve<CollisionSimulator>();
	simulator_ptr->add_reciever(&collider);

	//画像のロード 
	img_handle = handler_owner->load_graph("enemy.png");
	bgm_handle = handler_owner->load_audio("score.mp3");

	//武器の初期化 
	weapons = new WeaponCollection(&shoot_point, handler_owner.get(), simulator_ptr.get());
	weapons->set_channels(0);
	weapons->add_weapon<WeaponA>();
};

EnemyA::~EnemyA()
{
	delete weapons;
	delete death_delay;
}

void EnemyA::damage(int damage)
{
	hit_point.decrease(damage);
}

void EnemyA::spawn(Vector2 pos, Vector2 initial_velocity)
{
	position = pos;
	shoot_point = pos;
	velocity_mov = initial_velocity;
	rotation = 0;
	pos_delta.x = pos.x;
	pos_delta.y = pos.y;

	enable();
}

void EnemyA::update_status()
{
	//公転の半径 + 自身の半径 
	const	int radius = (int)(rotate_radius + collider.collision.radius);
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
		else if (death_delay->complete()) //300ミリ秒後に自滅
		{
			disable();
		}
	}
}

void EnemyA::update(const double& dt)
{
	if (!enabled) return;

	if (is_showing)
	{
		update_movement(dt);
		shoot_point = position + Vector2(0, 10);

		shoot_repeater.update();
		weapons->update(dt);
	}

	update_status();
};

void EnemyA::update_movement(const double& dt)
{
	Vector2 rot_delta = Vector2(0, 0);

	if (is_rotate)
	{
		//公転する 
		rotation = repeat(rotation + (float)(velocity_rot * dt), (float)(2 * PI));
		rot_delta.x = cos(rotation) * rotate_radius;
		rot_delta.y = sin(rotation) * rotate_radius;
	}


	//速度 + 公転の差分
	position += (velocity_mov + rot_delta) * (float)dt;
}

void EnemyA::draw()
{
	if (!enabled || !is_showing) return;

	const Vector2Int& pos = (Vector2Int)position;
	handler_owner->draw_extend_graph(pos.x, pos.y, 4, img_handle);

	weapons->draw();
};

void EnemyA::enable()
{
	enabled = true;
	collider.simulated = true;
	is_showing = true;
};

void EnemyA::hide()
{
	collider.simulated = false;
	weapons->reset_all();
	is_showing = false;
}

void EnemyA::disable()
{
	enabled = false;
};


