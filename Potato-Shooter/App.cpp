#include "App.h"
#include "Extension.h"

//描画ウィンドウの幅 
int App::screen_w = 0;

//描画ウィンドウの高さ
int App::screen_h = 0;

//DxLib, アプリケーションの初期化
int App::initialize()
{
	ChangeWindowMode(TRUE); //TRUE = Window Mode, FALSE = Full Screen Mode

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	init_rand();

	SetDrawScreen(DX_SCREEN_BACK);

	GetDrawScreenSize(&screen_w, &screen_h);

	return 0;
}

//DxLibの更新メソッドをまとめて実行
int App::refresh_frame()
{
	//一応判別できるように値は分ける 
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -2;
	if (ClearDrawScreen() != 0) return -3;
	if (clsDx() != 0) return -4;

	return 0;
}


void App::finalize()
{
	DxLib_End();
}
