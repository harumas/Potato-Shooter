#pragma once

#include "Weapon.h" 

struct BulletB
{
	BulletB(int channel);

	Vector2 position = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);
	Vector2 shoot_dir = Vector2(0, 0);

	SenderCollision collider;

	void enable();
	void disable();
	bool exist() const;

private:
	bool is_alive = false;
	int damage_point = 3;
};

class WeaponB : public Weapon
{
private:
	std::vector<BulletB*> bullets;
	const Vector2* target;
	bool is_flip_shoot = false;

	const float shoot_offset = 20;
	const float shoot_range = 10;
	const int bullet_count = 10;
	const int shoot_interval = 600;
	const float bullet_height = 40;

	int bullet_handle;

	void update_bullet(BulletB* bullet, const double& dt);
	void update_bullet_status(BulletB* bullet);
	Vector2 calc_direction();
	Vector2 calc_right();

public:
	~WeaponB();

	void load(ResourceHandler* handler, CollisionSimulator* simulator) override;
	void set_target(const Vector2* target);
	void create(const Vector2* base_point) override;
	void shoot(Vector2 initial_velocity) override;
	void update(const double& dt) override;
	void draw() override;
	void reset() override;
};



