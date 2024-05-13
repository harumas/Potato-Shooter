#pragma once

#include "Task.h"
#include "EnemyB.h" 

class EnemyBTurretTask :public Task
{
public:
	void initialize(ServiceLocator& locator) override
	{
		for (int i = 0; i < spawn_amount; i++)
		{
			enemies_B.emplace_back(new EnemyB(locator));
		}
	}

	void spawn_enemies()
	{
		if (GetNowCount() < prev_spawn_time + spawn_interval) return;

		float x = 30.0f + (App::screen_w - 60.0f) * rand_int(0, 1);

		const	Vector2 position = Vector2(x, -40);
		const Vector2 initial_velocity = Vector2(0, 50);
		enemies_B[current_spawn_count]->spawn(position, initial_velocity);

		prev_spawn_time = GetNowCount();
		current_spawn_count++;
	}

	bool is_starting() override
	{
		return current_spawn_count < spawn_amount;
	}

	void start() override
	{
		spawn_enemies();
	}

	bool is_executing() override
	{
		for (const EnemyB* enemy : enemies_B)
		{
			if (enemy->is_enabled())
				return true;
		}

		return false;
	}

	void execute(const double& dt) override
	{
		for (EnemyB* enemy : enemies_B)
		{
			enemy->update(dt);
		}
	};

	void draw() override
	{
		for (EnemyB* enemy : enemies_B)
		{
			enemy->draw();
		}
	};

private:
	const int spawn_interval = 1500;
	const int spawn_amount = 4;

	int current_spawn_count = 0;
	int prev_spawn_time = 0;

	std::vector<EnemyB*> enemies_B;
};


