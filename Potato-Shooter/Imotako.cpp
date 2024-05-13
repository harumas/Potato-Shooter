#include "Imotako.h"

Imotako::Imotako(ServiceLocator& locator) :
	collider(1, &position, 35.0f, [this](int damage) { this->damage(damage); }),
	target(locator.resolve<Player>()->get_position()),
	Entity(locator)
{
	game_score = locator.resolve<GameScore>();

	//コライダーを登録 
	simulator_ptr = locator.resolve<CollisionSimulator>();
	simulator_ptr->add_reciever(&collider);

	//画像のロード 
	img_handle_body = handler_owner->load_graph("imotako.png");
	img_handle_splash = handler_owner->load_graph("imotako_splash.png");
	score_handle = handler_owner->load_audio("score.mp3");
	splash_handle = handler_owner->load_audio("splash.mp3");
};

void Imotako::damage(int damage)
{
	hit_point.decrease(damage);
}

void Imotako::spawn(Vector2 pos, Vector2 initial_velocity)
{
	position = pos;
	velocity = initial_velocity;
	arrive_time = arrive_time_schedule;

	enable();
}

void Imotako::update_status()
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
			death_delay = new DelayPromise(400);

			if (is_dead)
			{
				game_score->add(100);
				explode_effect.play(position, 0.4);
				PlaySoundMem(score_handle, DX_PLAYTYPE_BACK);
			}

			hide();
		}
		else if (death_delay->complete())
		{
			disable();
		}
	}
}

void Imotako::update(const double& dt)
{
	if (!enabled) return;

	if (is_showing)
	{
		is_targeting = arrive_time > 0.3f;

		if (is_targeting)
		{
			adjust_velocity((float)dt);
		}
		else
		{
			update_splash(dt);
		}

		if (!is_exploding)
		{
			position += velocity * (float)dt;
		}
	}

	update_status();
};

void Imotako::update_splash(const double& dt)
{
	if (!is_exploding && !is_escaping)
	{
		explode_timer = new DelayPromise(explode_time);
		is_exploding = true;
	}
	else
	{
		notice_time += dt * 10.0;

		if (explode_timer->complete())
		{
			if (is_exploding)
			{
				splash();
			}
			else
			{
				if (escape_timer->complete())
				{
					disable();
				}
			}
		}
	}
}


void Imotako::splash()
{
	is_splashing = is_splash_range();
	splash_position = position;
	escape_timer = new DelayPromise(escape_time);
	velocity = escape_velocity;

	if (is_splashing)
	{
		PlaySoundMem(splash_handle, DX_PLAYTYPE_BACK);
	}

	is_exploding = false;
	is_escaping = true;
}

void Imotako::adjust_velocity(const float dt)
{
	//等加速度運動に沿って算出
	Vector2 diff = *target - position;
	Vector2 acceleration = (diff - velocity * arrive_time) * 2.0f / (arrive_time * arrive_time);

	arrive_time -= dt;
	velocity += acceleration * dt;
}

bool Imotako::is_splash_range()
{
	const Vector2 dist = *target - position;

	return dist.x * dist.x + dist.y * dist.y <= splash_range * splash_range;
}

void Imotako::draw()
{
	if (!enabled || !is_showing) return;

	const Vector2Int& pos = (Vector2Int)position;

	double body_size = is_exploding ? 5 : 3.5;
	handler_owner->draw_extend_graph(pos.x, pos.y, body_size, img_handle_body);

	if (is_exploding)
	{
		//警告用の半透明な円 
		int alpha = (int)(30 * sin(notice_time) + 50);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawCircle(pos.x, pos.y, (int)splash_range, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
};

void Imotako::post_draw()
{
	if (is_splashing)
	{
		const Vector2Int& splash_pos = (Vector2Int)splash_position;
		handler_owner->draw_extend_graph(splash_pos.x, splash_pos.y, 10, img_handle_splash);
	}
}

void Imotako::enable()
{
	enabled = true;
	collider.simulated = true;
	is_showing = true;
};

void Imotako::hide()
{
	collider.simulated = false;
	is_showing = false;
}

void Imotako::disable()
{
	collider.simulated = false;
	is_splashing = false;
	enabled = false;
};

