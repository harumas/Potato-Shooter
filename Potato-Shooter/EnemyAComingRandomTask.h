#pragma once

#include "Task.h"
#include "EnemyA.h" 


class EnemyAComingRandomTask :public Task
{
public:
	~EnemyAComingRandomTask()
	{
		delete position_list;

		for (EnemyA* enemy : enemies_A)
		{
			delete enemy;
		}
	}

	void initialize(ServiceLocator& locator) override
	{
		for (int i = 0; i < spawn_amount; i++)
		{
			enemies_A.emplace_back(new EnemyA(locator, false));
		}

		position_list = new int[spawn_amount];

		for (int i = 0; i < spawn_amount; i++)
		{
			position_list[i] = (i + 1) * spawn_space;
		}

		shuffle(position_list, spawn_amount);
	}

	void spawn_enemies()
	{
		if (GetNowCount() < prev_spawn_time + spawn_interval) return;

		const	Vector2 position = Vector2((float)position_list[current_spawn_count], -20);
		const Vector2 initial_velocity = Vector2(0, 50);
		enemies_A[current_spawn_count]->spawn(position, initial_velocity);

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
	const int spawn_interval = 500;
	const int spawn_amount = 10;
	const int spawn_space = 100;

	int current_spawn_count = 0;
	int prev_spawn_time = 0;

	std::vector<EnemyA*> enemies_A;
	int* position_list;
};

