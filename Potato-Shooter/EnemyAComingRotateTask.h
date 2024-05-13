#pragma once

#include "Task.h"
#include "EnemyA.h" 

class EnemyAComingRotateTask :public Task
{
public:
	void initialize(ServiceLocator& locator) override
	{
		for (int i = 0; i < spawn_amount * spawn_count; i++)
		{
			enemies_A.emplace_back(new EnemyA(locator, true));
		}
	};

	void spawn_enemies()
	{
		//一列づつタイミングをずらしながらスポーン(塊ごとに描画するわけではない)
		if (GetNowCount() < prev_spawn_time + spawn_interval) return;

		int spawn_range = App::screen_w;
		const float unit = 1.0f / spawn_amount; //スポーンする場所の割合
		const int pivot = current_spawn_count * spawn_amount; //今までにスポーンした数
		const Vector2 initial_velocity = Vector2(0, 50);

		for (int i = pivot; i < pivot + spawn_amount; i++)
		{
			float spawn_offset = spawn_range * (unit * (i % spawn_amount));

			Vector2 position = Vector2(60 + spawn_offset, 0);
			enemies_A[i]->spawn(position, initial_velocity);
		}

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
	const int spawn_interval = 200;
	const int spawn_amount = 5;
	const int spawn_count = 5;

	int current_spawn_count = 0;
	int prev_spawn_time = 0;

	std::vector<EnemyA*> enemies_A;
};

