#include "Device.h"

void Device::update()
{
	is_key_input = CheckHitKeyAll(DX_CHECKINPUT_KEY);
	GetHitKeyStateAll(*keybuf_now);
	GetMousePoint(&mouse_x, &mouse_y);

	mouse_input_old = mouse_input_now;
	mouse_input_now = GetMouseInput();

	swap_buffer(keybuf_now, keybuf_old); //入力バッファポインタの入れ替え
}

void Device::swap_buffer(char** a, char** b)
{
	char* tmp = *a;
	*a = *b;
	*b = tmp;
}

bool Device::is_mouse_down(int type)
{
	return (mouse_input_now & type) == 1 && (mouse_input_old & type) == 0;
}

bool Device::is_mouse(int type)
{
	return mouse_input_now & type;
}

bool Device::is_mouse_up(int type)
{
	return (mouse_input_now & type) == 0 && (mouse_input_old & type) == 1;
}

bool Device::is_key_down(int type)
{
	return (*keybuf_now)[type] == 1 && (*keybuf_old)[type] == 0;
}

bool Device::is_key(int type)
{
	return (*keybuf_now)[type];
}

bool Device::is_key_up(int type)
{
	return (*keybuf_now)[type] == 0 && (*keybuf_old)[type] == 1;
}

bool Device::is_any_key()
{
	return is_key_input;
}

int Device::get_virtual_input(int type)
{
	//x軸の入力 
	if (type == KEY_INPUT_HORIZONTAL)
	{
		if (is_key(KEY_INPUT_RIGHT) || is_key(KEY_INPUT_D)) return 1;
		if (is_key(KEY_INPUT_LEFT) || is_key(KEY_INPUT_A)) return -1;
	}

	//y軸の入力(画面上の座標なので上下は反対)
	if (type == KEY_INPUT_VIRTICAL)
	{
		if (is_key(KEY_INPUT_UP) || is_key(KEY_INPUT_W)) return -1;
		if (is_key(KEY_INPUT_DOWN) || is_key(KEY_INPUT_S)) return 1;
	}

	return 0;
}
