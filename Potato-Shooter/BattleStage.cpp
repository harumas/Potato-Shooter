#include "GameScene.h"
#include "Entities.h"

void BattleStage::load(ServiceLocator& locator)
{
	Scene::load(locator);

	//依存を解決 
	device = locator.resolve<Device>();
	timer = locator.resolve<Time>();
	player = locator.resolve<Player>();
	simulator = locator.resolve<CollisionSimulator>();
	game_score = locator.resolve<GameScore>();

	loading_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5, DX_FONTTYPE_EDGE);;
	bgm_handle = handler->load_audio("battle.mp3");

	task_system = new TaskSystem(locator);
	scroller = new BackScroller(handler.get());
};

void BattleStage::init()
{
	//プレイヤーを初期化
	player->reload();
	player->enable_input = true;
	player->set_position(App::screen_w / 2.0f, App::screen_h - 50.0f);
	player->enable();

	//バトルのタスクを作成
	create_tasks();

	//BGMを再生
	PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP);

	initialized = true;
}

void BattleStage::create_tasks()
{
	TaskSystem& list = *task_system;

	list.add<TutorialTask>();
	list.add<EnemyAComingRandomTask>();
	list.add<EnemyAComingRandomTask>();
	list.delay(2000);
	list.add<EnemyBTurretTask>();
	list.add<EnemyAComingRandomTask>();
	list.delay(3000);
	list.add<ImotakoComingTask>();
	list.add<EnemyAComingRotateTask>();
	list.delay(3000);
	list.add<EnemyAComingSlashTask>();
	list.add<EnemyAComingRandomTask>();
	list.delay(2000);
	list.add<EnemyBTurretTask>();
	list.add<EnemyAComingSlashTask>();
	list.delay(2000);
	list.add<EnemyAComingRotateTask>();
	list.add<ImotakoComingTask>();
}

int BattleStage::update()
{
	//ESCAPEで終了
	if (device->is_key_down(KEY_INPUT_ESCAPE))
	{
		return quit();
	}

	//Iで当たり判定を表示
	if (device->is_key_down(KEY_INPUT_I))
	{
		show_collision = !show_collision;
	}

	double dt = timer->get_delta();

	scroller->update(dt);
	player->update(dt);
	task_system->update(dt);
	simulator.get()->update();

	if (is_game_end())
	{
		bool game_clear = is_game_clear();
		return game_end_loop(game_clear);
	}

	return proceed();
}


bool BattleStage::is_game_end()
{
	return task_system->finished() || player->is_death();
}

bool BattleStage::is_game_clear()
{
	if (task_system->finished())
	{
		return true;
	}

	if (player->is_death())
	{
		return false;
	}

	return false;
}

int BattleStage::game_end_loop(bool game_clear)
{
	if (game_over_delay == nullptr)
	{
		//スローモーション
		timer->set_time_scale(0.25);
		player->enable_input = false;
		game_over_delay = new DelayPromise(3000);

		if (game_clear)
		{
			//クリアとして設定
			game_score->set_status(true);
		}
	}

	if (game_over_delay->complete())
	{
		return sequence_to(SceneName::GameOver);
	}

	return proceed();
}

void BattleStage::draw()
{
	scroller->draw();
	player->draw();
	task_system->draw();
	task_system->post_draw();
	player->draw_status();
	game_score->draw();

	if (show_collision)
	{
		simulator->debug_draw();
	}
}


void BattleStage::clear()
{
	player->reset();
	timer->set_time_scale(1);
	task_system->clear();
	simulator->reset();

	delete game_over_delay;
	game_over_delay = nullptr;

	StopSoundMem(bgm_handle);

	initialized = false;
}



