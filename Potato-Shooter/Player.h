#pragma once
#include "Entity.h"
#include "HP.h"
#include "Repeater.h"
#include "Effect.h"
#include "CollisionSimulator.h"
#include "WeaponCollection.h"

class PlayerStatus
{
public:
	PlayerStatus(ResourceHandler* handler);

	void increase(int delta);
	void decrease(int delta);
	void draw();
	void reset();

	std::function<void(void)> on_death;

private:
	HP hit_point = HP(20, 20);
	int heart_handle;
	int heart_half_handle;
};


class Player : public Entity
{
private:
	std::shared_ptr<Device> device_ptr; //インスタンスの所有権
	std::shared_ptr<CollisionSimulator> simulator_ptr; //インスタンスの所有権

	int player_handle;
	int shoot_handle;
	int damage_handle;
	int dead_handle;

	Vector2 position = Vector2(App::screen_w / 2.0f, App::screen_h - 50.0f);
	Vector2 shoot_point = Vector2(0, 0);
	Vector2 speed = Vector2(350.0f, 350.0f);
	Vector2 weapon_velocity = Vector2(0, -400);
	Effect explode_effect = Effect("explode_sheet.png", 5, 16, 12);

	RecieverCollision collider;
	PlayerStatus status;
	WeaponCollection* weapons = nullptr;
	Repeater* auto_shooter = nullptr;

	bool is_death_flag = false;
	bool is_auto_shoot = false;
	bool reloaded = false;

	void update_movement(Device& device, const double& dt);
	void update_shooter();
	void damage(int damage);
	void adjust_position();
	void shoot();

public:
	Player(ServiceLocator& locator);
	~Player();

	bool enable_input = true;

	void update(const double& dt) override;
	void move(float x, float y, const double& dt);
	void reload();
	bool is_death();
	void set_position(float x, float y);
	const	Vector2* get_position();
	void draw() override;
	void draw_status();
	void enable() override;
	void disable() override;
	void reset();
};

