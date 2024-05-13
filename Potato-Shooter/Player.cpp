#include "Player.h"
#include "WeaponA.h" 

Player::Player(ServiceLocator& locator) :
	Entity(locator), status(handler_owner.get()),
	collider(0, &position, 15.0f, [&](int dmg) { damage(dmg); })
{
	device_ptr = locator.resolve<Device>();
	simulator_ptr = locator.resolve<CollisionSimulator>();

	//画像のロード 
	player_handle = handler_owner->load_graph("player.png");
	shoot_handle = handler_owner->load_audio("shoot.mp3");
	damage_handle = handler_owner->load_audio("damage.mp3");
	dead_handle = handler_owner->load_audio("dead.mp3");

	status.on_death = [this]() { this->is_death_flag = true; };
}

void Player::reload()
{
	if (reloaded) return;

	simulator_ptr->add_reciever(&collider);

	//武器の初期化 
	weapons = new WeaponCollection(&shoot_point, handler_owner.get(), simulator_ptr.get());
	weapons->set_channels(1);
	weapons->add_weapon<WeaponA>();

	reloaded = true;
}

void Player::damage(int damage)
{
	if (is_death()) return;

	status.decrease(damage);

	int dmg_handle = is_death() ? dead_handle : damage_handle;
	PlaySoundMem(dmg_handle, DX_PLAYTYPE_BACK);

	if (is_death())
	{
		explode_effect.play(position + Vector2(5, 0), 0.5);
	}
}

void Player::update(const double& dt)
{
	Device& device = *device_ptr.get();

	//自滅 
	if (device.is_key_down(KEY_INPUT_K))
	{
		damage(INT_MAX);
		return;
	}

	if (!enable_input) return;

	update_shooter(); //自動発射モード
	update_movement(device, dt);

	//Zで発射
	if (device.is_key_down(KEY_INPUT_Z))
	{
		shoot();
	}

	weapons->update(dt);
}


void Player::update_shooter()
{
	//Oで自動発射モードに切り替え 
	if (device_ptr->is_key_down(KEY_INPUT_O))
	{
		is_auto_shoot = !is_auto_shoot;

		if (is_auto_shoot)
		{
			delete auto_shooter;
			auto_shooter = new Repeater(0.35, [this]() { shoot(); });
		}
	}

	if (is_auto_shoot)
	{
		auto_shooter->update();
	}
}

void Player::shoot()
{
	weapons->shoot(weapon_velocity);
	PlaySoundMem(shoot_handle, DX_PLAYTYPE_BACK);
}

void Player::update_movement(Device& device, const double& dt)
{
	int input_x = device.get_virtual_input(KEY_INPUT_HORIZONTAL);
	int input_y = device.get_virtual_input(KEY_INPUT_VIRTICAL);

	//入力を方向ベクトルに変換 
	Vector2 input = { (float)input_x, (float)input_y };
	input = input.normalized();

	move(input.x, input.y, dt);
}

void Player::move(float x, float y, const double& dt)
{
	position.x += (float)(x * speed.x * dt);
	position.y += (float)(y * speed.y * dt);

	adjust_position();
}

void Player::set_position(float x, float y)
{
	position.x = x;
	position.y = y;

	adjust_position();
}

void Player::adjust_position()
{
	//画面範囲外に出ないようにする
	const float radius = collider.collision.radius;
	position.x = clamp(radius, App::screen_w - radius, position.x);
	position.y = clamp(radius, App::screen_h - radius, position.y);

	shoot_point = position + Vector2(0, -40);
}

void Player::draw()
{
	ResourceHandler& handler = *handler_owner.get();

	if (!is_death())
	{
		const	Vector2Int& pos = (Vector2Int)position;
		handler.draw_extend_graph(pos.x, pos.y, 5, player_handle);
	}

	weapons->draw();
}

bool Player::is_death()
{
	return is_death_flag;
}

const Vector2* Player::get_position()
{
	return &position;
}

void Player::draw_status()
{
	status.draw();
}

void Player::enable()
{
	enabled = true;
	collider.simulated = true;
}

void Player::disable()
{
	enabled = false;
	collider.simulated = false;
}

void Player::reset()
{
	is_death_flag = false;
	position = Vector2(App::screen_w / 2.0f, App::screen_h - 50.0f);
	status.reset();

	delete weapons;
	delete auto_shooter;

	reloaded = false;
}

Player::~Player()
{
	delete weapons;
}
