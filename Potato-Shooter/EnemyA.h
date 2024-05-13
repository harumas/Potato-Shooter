#pragma once

#include "Entities.h" 
#include "Module.h" 
#include "Repeater.h" 

class EnemyA : public Entity
{
private:
	std::shared_ptr<CollisionSimulator> simulator_ptr; //インスタンスの所有権
	std::shared_ptr<GameScore> game_score;

	HP hit_point = HP(1, 1);
	RecieverCollision collider;
	Repeater shoot_repeater;
	WeaponCollection* weapons = nullptr;

	Effect explode_effect = Effect("explode_sheet.png", 9, 16, 4);
	DelayPromise* death_delay = nullptr;

	Vector2 position = Vector2(0, 0);
	Vector2 shoot_point = Vector2(0, 0);
	Vector2 pos_delta = Vector2(0, 0);
	Vector2 velocity_mov = Vector2(0, 0);

	float rotation;
	float velocity_rot = 5;
	int rotate_radius = 130;

	int img_handle;
	int bgm_handle;

	bool is_rotate;
	bool is_showing = true;

	void update_movement(const double& dt);

public:
	EnemyA(ServiceLocator& locator, bool is_rotate);
	~EnemyA();

	void spawn(Vector2 position, Vector2 initial_velocity);
	void damage(int damage);
	void update_status();
	void update(const double& dt) override;
	void draw() override;
	void enable() override;
	void hide();
	void disable() override;
};




