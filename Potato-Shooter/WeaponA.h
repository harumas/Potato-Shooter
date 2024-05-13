#pragma once

#include "Weapon.h" 

struct BulletA
{
	BulletA(int channel);

	Vector2 position = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);

	SenderCollision collider;

	void enable();
	void disable();
	bool exist() const;

private:
	bool is_alive = false;
	int damage_point = 1;
};

class WeaponA : public Weapon
{
private:
	std::vector<BulletA*> bullets;
	int bullet_handle;
	int bullet_count;

	void update_bullet(BulletA* bullet, const double& dt);
	void update_bullet_status(BulletA* bullet);

public:
	WeaponA();
	~WeaponA();

	void load(ResourceHandler* handler, CollisionSimulator* simulator) override;
	void create(const Vector2* base_point) override;
	void shoot(Vector2 initial_velocity) override;
	void update(const double& dt) override;
	void draw() override;
	void reset() override;
};



