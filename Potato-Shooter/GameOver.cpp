#include "GameScene.h"

void GameOver::load(ServiceLocator& locator)
{
	Scene::load(locator);

	//依存を解決 
	game_score = locator.resolve<GameScore>();
	player = locator.resolve<Player>();

	hud_font_handle = CreateFontToHandle("BIZ UD Gothic", 12, 5, DX_FONTTYPE_EDGE);
	clear_handle = handler->load_audio("clear.mp3");
	failed_handle = handler->load_audio("failed.mp3");

	//ボタンのコールバックを登録 
	retry_button.on_click = [this]() { is_retry = true; };
	home_button.on_click = [this]() { is_home = true; };
};

void GameOver::init()
{
	retry_button.enable();
	home_button.enable();

	int bgm_handle = game_score->is_clear() ? clear_handle : failed_handle;
	PlaySoundMem(bgm_handle, DX_PLAYTYPE_BACK);

	initialized = true;
}

int GameOver::update()
{
	//ESCAPEで終了
	if (device->is_key_down(KEY_INPUT_ESCAPE))
	{
		return quit();
	}

	if (is_home)
	{
		return sequence_to(SceneName::StartMenu);
	}

	if (is_retry)
	{
		return sequence_to(SceneName::BattleStage);
	}

	return proceed();
}

void GameOver::draw()
{
	//背景 
	DrawBox(0, 0, App::screen_w, App::screen_h, GetColor(235, 229, 164), TRUE);

	//"Score"
	unsigned int font_color = GetColor(255, 255, 255);
	unsigned int edge_color = GetColor(225, 170, 36);
	DrawRotaStringToHandle(220, 80, 5, 5, 0, 0, 0, font_color, hud_font_handle, edge_color, 0, "Score");


	//スコア表示
	unsigned int edge_color_score = GetColor(238, 134, 106);

	string _str = to_string(game_score->get());
	const char* str = _str.c_str();
	int	half_font_width = GetDrawStringWidthToHandle(str, (int)strlen(str), hud_font_handle) * 5;
	DrawRotaStringToHandle((App::screen_w - half_font_width) / 2, 200, 5, 5, 0, 0, 0, font_color, hud_font_handle, edge_color_score, 0, str);
}

void GameOver::clear()
{
	retry_button.disable();
	home_button.disable();

	is_retry = false;
	is_home = false;

	game_score->reset();

	initialized = false;
}
