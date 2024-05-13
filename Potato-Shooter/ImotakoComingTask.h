#pragma once

#include "Task.h"
#include "Imotako.h" 


class ImotakoComingTask :public Task
{
public:
	void initialize(ServiceLocator& locator) override
	{
		for (int i = 0; i < spawn_amount; i++)
		{
			enemies.emplace_back(new Imotako(locator));
		}

		position_list = (int*)malloc(sizeof(int) * spawn_amount);

		for (int i = 0; i < spawn_amount; i++)
		{
			position_list[i] = (i + 1) * spawn_space;
		}

		shuffle(position_list, spawn_amount);
	}

	void spawn_enemies()
	{
		if (GetNowCount() < prev_spawn_time + spawn_interval) return;

		const	Vector2 position = Vector2((float)position_list[current_spawn_count], 0);
		const Vector2 initial_velocity = Vector2(0, 50);
		enemies[current_spawn_count]->spawn(position, initial_velocity);

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
		for (const Imotako* enemy : enemies)
		{
			if (enemy->is_enabled())
				return true;
		}

		return false;
	}

	void execute(const double& dt) override
	{
		for (Imotako* enemy : enemies)
		{
			enemy->update(dt);
		}
	};

	void draw() override
	{
		for (Imotako* enemy : enemies)
		{
			enemy->draw();
		}
	};

	void post_draw() override
	{
		for (Imotako* enemy : enemies)
		{
			enemy->post_draw();
		}
	}

private:
	const int spawn_interval = 1500;
	const int spawn_amount = 5;
	const int spawn_space = 100;

	int current_spawn_count = 0;
	int prev_spawn_time = 0;

	std::vector<Imotako*> enemies;
	int* position_list;
};

