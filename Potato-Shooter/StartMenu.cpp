#include <future>
#include <thread>
#include <chrono>
#include "GameScene.h"

void StartMenu::load(ServiceLocator& locator)
{
	Scene::load(locator);

	hud_font_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5, DX_FONTTYPE_EDGE);
	bgm_handle = handler->load_audio("title.mp3");

	//依存を解決 
	timer = locator.resolve<Time>();
	player = locator.resolve<Player>();
};

void StartMenu::init()
{
	//プレイヤーの初期化 
	player->reload();
	player->enable_input = false;
	start_button.enable();
	start_button.on_click = [this]() { game_started = true; };

	//プレイヤーを中心に設定
	player->set_position(App::screen_w / 2.0f, App::screen_h / 2.0f + 30);
	player->enable();

	PlaySoundMem(bgm_handle, DX_PLAYTYPE_LOOP);

	initialized = true;
}

int StartMenu::update()
{
	//ESCAPEで終了
	if (device->is_key_down(KEY_INPUT_ESCAPE))
	{
		return quit();
	}

	double dt = timer->get_delta();
	player->update(dt);

	if (game_started)
	{
		return sequence_to(SceneName::BattleStage);
	}

	return proceed();
}

void StartMenu::draw()
{
	//背景
	DrawBox(0, 0, App::screen_w, App::screen_h, GetColor(235, 229, 164), TRUE);

	player->draw();

	//タイトルロゴ
	unsigned int font_color = GetColor(255, 255, 255);
	unsigned int edge_color = GetColor(225, 170, 36);
	DrawRotaStringToHandle(50, 80, 5, 5, 0, 0, 0, font_color, hud_font_handle, edge_color, 0, "Potato Shooter");
}

void StartMenu::clear()
{
	start_button.disable();
	game_started = false;

	StopSoundMem(bgm_handle);

	initialized = false;
}


