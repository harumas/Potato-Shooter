#pragma once

#include "Entities.h" 
#include "WeaponB.h" 
#include "Module.h" 
#include "Repeater.h" 
#include "DelayPromise.h"

class Imotako : public Entity
{
private:
	std::shared_ptr<CollisionSimulator> simulator_ptr; //インスタンスの所有権
	std::shared_ptr<GameScore> game_score;

	HP hit_point = HP(5, 5);

	RecieverCollision collider;

	DelayPromise* escape_timer = nullptr;
	DelayPromise* explode_timer = nullptr;
	DelayPromise* death_delay = nullptr;
	Effect explode_effect = Effect("explode_sheet.png", 9, 16, 8);

	const Vector2* target;

	Vector2 position = Vector2(0, 0);
	Vector2 splash_position = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);
	Vector2 escape_velocity = Vector2(0, -800);

	float arrive_time_schedule = 2.0f;
	float arrive_time = 0.0f;
	float splash_range = 150.0f;
	int escape_time = 4000;
	int explode_time = 700;
	bool is_targeting = false;
	bool is_exploding = false;
	bool is_escaping = false;
	bool is_splashing = false;
	bool is_showing = true;

	int img_handle_body;
	int img_handle_splash;
	int score_handle;
	int splash_handle;

	double notice_time = 0;

	void adjust_velocity(const float dt);
	bool is_splash_range();
	void splash();
	void update_splash(const double& dt);

public:
	Imotako(ServiceLocator& locator);

	void spawn(Vector2 position, Vector2 initial_velocity);
	void damage(int damage);
	void update_status();
	void update(const double& dt) override;
	void draw() override;
	void post_draw() override;
	void enable() override;
	void hide();
	void disable() override;
};


