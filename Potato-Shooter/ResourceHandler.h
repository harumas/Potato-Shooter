#pragma once 
#include <string>
#include <math.h>
#include <unordered_map>
#include "DxLib.h"
#include "app.h"
#include "extension.h"

using namespace std;

class ResourceHandler
{
private:
	const string rootPath = ".\\media\\";

	const vector<string> support_graph{ ".png",".jpg",".bmp",".argb",".tga",".dds" };
	const vector<string> support_audio{ ".mp3",".ogg",".wav" };

	unordered_map<string, int> graph_handle_cache;
	unordered_map<string, int> audio_handle_cache;

public:

	//画像データをロードする
	int load_graph(const string path_data);

	//画像データをロードする
	int* load_div_graph(const string path_data, int count, int x_num, int y_num, int x_size, int y_size);

	//音声データをロードする
	int load_audio(const string path_data);

	//画像を描画する
	void draw_graph(int x, int y, int handle, bool scaleToScreen = false);

	//画像を拡縮して描画する
	void draw_extend_graph(int x, int y, double ext_rate, int handle);

	//画像を回転&拡縮して描画する
	void draw_rota_graph(int x, int y, int rot_offset, double angle, int handle, double ext_rate = 1.0, bool is_turn = false);

	~ResourceHandler();
};

