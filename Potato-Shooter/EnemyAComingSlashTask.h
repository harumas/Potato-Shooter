#pragma once

#include "Task.h"
#include "EnemyA.h" 

class EnemyAComingSlashTask :public Task
{
public:
	void initialize(ServiceLocator& locator) override
	{
		for (int i = 0; i < spawn_amount * spawn_count; i++)
		{
			enemies_A.emplace_back(new EnemyA(locator, false));
		}
	};

	void spawn_enemies()
	{
		//１塊のスポーンを終えたらインターバルを挟む 
		if (GetNowCount() < prev_spawn_time + spawn_interval) return;

		const float flip_unit = is_flip ? -1.0f : 1.0f;
		const int spawn_offset = is_flip ? App::screen_w : 0;
		const int pivot = current_spawn_count * spawn_amount;
		const Vector2 initial_velocity = Vector2(flip_unit * 120, 150);

		for (int i = pivot; i < pivot + spawn_amount; i++)
		{
			float space = (float)(spawn_space * (i % spawn_amount + 1));
			Vector2 position = Vector2(spawn_offset - flip_unit * space, -space);
			enemies_A[i]->spawn(position, initial_velocity);
		}

		is_flip = !is_flip;

		prev_spawn_time = GetNowCount();
		current_spawn_count++;
	}

	bool is_starting() override
	{
		return current_spawn_count < spawn_count;
	}

	void start() override
	{
		spawn_enemies();
	}

	bool is_executing() override
	{
		for (const EnemyA* enemy : enemies_A)
		{
			if (enemy->is_enabled())
				return true;
		}

		return false;
	}

	void execute(const double& dt) override
	{
		for (EnemyA* enemy : enemies_A)
		{
			enemy->update(dt);
		}
	};

	void draw() override
	{
		for (EnemyA* enemy : enemies_A)
		{
			enemy->draw();
		}
	};

private:
	const int spawn_interval = 4000;
	const int spawn_amount = 5;
	const int spawn_count = 3;
	const int spawn_space = 50;

	int current_spawn_count = 0;
	int prev_spawn_time = 0;

	bool is_flip = false;

	std::vector<EnemyA*> enemies_A;
};


