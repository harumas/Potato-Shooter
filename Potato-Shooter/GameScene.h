#pragma once

#include "Module.h"
#include "Entities.h"
#include "Tasks.h" 
#include "DelayPromise.h" 
#include "NormalButton.h" 
#include "MinimumButton.h" 
#include "BackScroller.h" 

enum class SceneName
{
	StartMenu = 1,
	BattleStage,
	GameOver,
	EndMenu
};

class StartMenu : public Scene
{
public:
	void load(ServiceLocator& locator) override;
	void init() override;
	int update() override;
	void draw() override;
	void clear() override;

private:
	int hud_font_handle = 0;
	int bgm_handle = 0;
	NormalButton start_button = NormalButton(App::screen_w / 2, 380, 160, 100, "Go!");

	std::shared_ptr<Time> timer;
	shared_ptr<Player> player = nullptr;

	bool game_started = false;

	void on_start();
	int sequence_to(SceneName name)
	{
		return static_cast<int>(name);
	}
};

class BattleStage : public Scene
{
public:
	void load(ServiceLocator& locator) override;
	void init() override;
	int update() override;
	void draw() override;
	void clear() override;

private:
	int loading_handle = 0;
	int bgm_handle = 0;
	bool show_collision = false;

	std::shared_ptr<Time> timer;
	std::shared_ptr<Player> player;
	std::shared_ptr<CollisionSimulator> simulator;
	shared_ptr<GameScore> game_score;

	TaskSystem* task_system = nullptr;
	DelayPromise* game_over_delay = nullptr;
	BackScroller* scroller = nullptr;

	void create_tasks();
	int game_end_loop(bool game_clear);
	bool is_game_end();
	bool is_game_clear();



	int sequence_to(SceneName name)
	{
		return static_cast<int>(name);
	}
};

class GameOver : public Scene
{
public:
	void load(ServiceLocator& locator) override;
	void init() override;
	int update() override;
	void draw() override;
	void clear() override;

private:
	int hud_font_handle = 0;
	int clear_handle = 0;
	int failed_handle = 0;

	MinimumButton retry_button = MinimumButton(App::screen_w / 2 - 120, 380, 160, 100, "Retry");
	MinimumButton home_button = MinimumButton(App::screen_w / 2 + 120, 380, 160, 100, "Home");


	bool is_retry = false;
	bool is_home = false;

	shared_ptr<GameScore> game_score;
	shared_ptr<Player> player;

	int sequence_to(SceneName name)
	{
		return static_cast<int>(name);
	}
};



