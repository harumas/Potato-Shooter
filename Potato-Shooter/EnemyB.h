#pragma once

#include "Entities.h" 
#include "WeaponB.h" 
#include "Module.h" 
#include "Repeater.h" 
#include "DelayPromise.h"

class EnemyB : public Entity
{
private:
	std::shared_ptr<CollisionSimulator> simulator_ptr; //インスタンスの所有権
	std::shared_ptr<GameScore> game_score;

	HP hit_point = HP(3, 3);
	RecieverCollision collider;
	Repeater shoot_repeater;
	DelayPromise* delay_timer = nullptr;
	WeaponCollection* weapons = nullptr;

	Effect explode_effect = Effect("explode_sheet.png", 9, 16, 4);
	DelayPromise* death_delay = nullptr;

	const Vector2* target;
	Vector2 position = Vector2(0, 0);
	Vector2 pos_delta = Vector2(0, 0);
	Vector2 velocity_mov = Vector2(0, 0);

	float is_targeting = true;
	double rotation;
	double next_rotation;
	double velocity_rot = PI * 0.4;

	int img_handle;
	int bgm_handle;

	bool is_showing = true;

	double get_next_rotation();
	void update_movement(const double& dt);

public:
	EnemyB(ServiceLocator& locator);

	void spawn(Vector2 position, Vector2 initial_velocity);
	void damage(int damage);
	void update_status();
	void update(const double& dt) override;
	void draw() override;
	void enable() override;
	void hide();
	void disable() override;
};





