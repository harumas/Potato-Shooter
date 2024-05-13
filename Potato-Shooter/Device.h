#pragma once
#include "DxLib.h" 

#define KEY_INPUT_HORIZONTAL 0
#define KEY_INPUT_VIRTICAL 1

class Device
{
private:
	//キーバッファ 
	char keybuf_a[256] = { 0 };
	char keybuf_b[256] = { 0 };

	char* keybuf_a_p = keybuf_a;
	char* keybuf_b_p = keybuf_b;

	//キーバッファ交換用のポインタ
	char** keybuf_now = &keybuf_a_p;
	char** keybuf_old = &keybuf_b_p;

	int mouse_input_old;
	int mouse_input_now;
	bool is_key_input;

	void swap_buffer(char** a, char** b);

public:
	int mouse_x, mouse_y;

	//デバイス入力情報の更新
	void update();

	//マウスのボタンが押されたか?
	bool is_mouse_down(int type);

	//マウスのボタンが押されているか?
	bool is_mouse(int type);

	//マウスのボタンが離されたか?
	bool is_mouse_up(int type);

	//キーが離されたか？
	bool is_key_up(int type);

	//キーが押されているか？
	bool is_key(int type);

	//キーが押されたか？
	bool is_key_down(int type);

	//指定された仮想軸の入力を取得
	int get_virtual_input(int type);

	//いずれかキーが押されているか？
	bool is_any_key();
};
