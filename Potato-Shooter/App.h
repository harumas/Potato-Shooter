#pragma once

#include "DxLib.h"
#include <time.h>

class App
{
public:

	// 描画画面の高さ
	static int screen_w;

	// 描画画面の幅
	static int screen_h;

	// アプリケーションの初期化
	static int initialize();

	// DxLibのメイン関数をまとめて実行（この関数以外で使用禁止!）
	static int refresh_frame();

	// アプリケーションの終了処理
	static void finalize();
};
